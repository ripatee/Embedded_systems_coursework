#include <stdio.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/mqtt.h>

#include <lvgl.h>
#include <zephyr/drivers/display.h>

#include "sensors.h"
#include "buttons.h"
#include "lte.h"
#include "mqtt_connection.h"
#include "sms_wrapper.h"

#define TEMP_LIMIT                  30.0

#define SENSOR_THREAD_PRIORITY      7
#define COMM_THREAD_PRIORITY        9
#define DISPLAY_THREAD_PRIORITY     8

#define SENSOR_THREAD_STACKSIZE     (1024 * 2)
#define COMM_THREAD_STACKSIZE       (1024 * 2)
#define DISPLAY_THREAD_STACKSIZE    (1024 * 4)

#define SENSOR_THREAD_SLEEP_MS      (1000*5)
#define COMM_THREAD_SLEEP_MS        (1000*30)
#define DISPLAY_THREAD_SLEEP_MS     (1000*5)


// Thread declarations
int sensor_thread(void);
int comm_thread(void);
int display_thread(void);

K_THREAD_DEFINE(sensor_thread_id, SENSOR_THREAD_STACKSIZE, sensor_thread,
                NULL, NULL, NULL, SENSOR_THREAD_PRIORITY, 0, 0);
K_THREAD_DEFINE(comm_thread_id, COMM_THREAD_STACKSIZE, comm_thread,
                NULL, NULL, NULL, COMM_THREAD_PRIORITY, 0, 10000);
K_THREAD_DEFINE(display_thread_id, DISPLAY_THREAD_STACKSIZE, display_thread,
                NULL, NULL, NULL, DISPLAY_THREAD_PRIORITY, 0, 0);

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

static struct mqtt_client mqtt_client;
static struct pollfd fds;

double temp, humidity;

int sensor_thread(void)
{
    LOG_INF("Sensor thread started");
    sensors_init();

    while(true)
    {
        temp = get_temperature();
        humidity = get_humidity();

        if (temp > TEMP_LIMIT) 
        {
            sms_send_temp_alert(temp);
            k_msleep(SENSOR_THREAD_SLEEP_MS*20);
        }

        k_msleep(SENSOR_THREAD_SLEEP_MS);
    }
}

int comm_thread(void)
{
    LOG_INF("Communications thread started");

    int err;
    uint32_t connect_attempt = 0;
    char mqtt_msg[31];

    if (lte_modem_configure())
    {
        LOG_ERR("Failed to configure modem");
        return 0;
    }

    if (sms_init())
    {
        LOG_ERR("Initializing SMS failed");
    }

    if (mqtt_client_init_wrapper(&mqtt_client))
    {
        LOG_ERR("Failed to initialize MQTT client");
        return 0;
    }

do_connect:
    if (connect_attempt++ > 0)
    {
        LOG_INF("Reconnecting in %d seconds..", CONFIG_MQTT_RECONNECT_DELAY_S);
        k_sleep(K_SECONDS(CONFIG_MQTT_RECONNECT_DELAY_S));
    }

    if (mqtt_connect(&mqtt_client))
    {
        LOG_ERR("Error in mqtt_connect");
        goto do_connect;
    }

    // Used by MQTT polling
    if (mqtt_fds_init(&mqtt_client, &fds))
    {
        LOG_ERR("Error in fds_init.");
        return 0;
    }

    while(true)
    {

        // Format MQTT message and show it
        snprintfcb(mqtt_msg, sizeof(mqtt_msg), 
                   "Temp: %.2fC, Humidity: %.2f%%", temp, humidity);

        LOG_INF("%s", mqtt_msg);

        // MQTT related things to have connection alive and 
        // poll for received MQTT messages
        err = poll(&fds, 1, mqtt_keepalive_time_left(&mqtt_client));
        if (err < 0) {
            LOG_ERR("Error in poll(): %d", errno);
            break;
        }

        err = mqtt_live(&mqtt_client);
        if ((err != 0) && (err != -EAGAIN)) {
            LOG_ERR("Error in mqtt_live: %d", err);
            break;
        }

        if ((fds.revents & POLLIN) == POLLIN) {
            err = mqtt_input(&mqtt_client);
            if (err != 0) {
                LOG_ERR("Error in mqtt_input: %d", err);
                break;
            }
        }

        if ((fds.revents & POLLERR) == POLLERR) {
            LOG_ERR("POLLERR");
            break;
        }

        if ((fds.revents & POLLNVAL) == POLLNVAL) {
            LOG_ERR("POLLNVAL");
            break;
        }

        // Send the sensor data to MQTT broker
        if (mqtt_data_publish(&mqtt_client, MQTT_QOS_1_AT_LEAST_ONCE,
                              mqtt_msg, sizeof(mqtt_msg)))
        {
            LOG_ERR("Failed to send MQTT message");
        }

        k_msleep(COMM_THREAD_SLEEP_MS);

    }

    LOG_INF("Disconnecting MQTT client");

    err = mqtt_disconnect(&mqtt_client);
    if (err) {
        LOG_ERR("Could not disconnect MQTT client: %d", err);
    }
    goto do_connect;
}

int display_thread(void)
{
    LOG_INF("Display thread started");

    const struct device *display_dev;
    lv_obj_t *hello_world_label;
    lv_obj_t *measurement_label;

    char count_str[19] = {0};

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev))
    {
        LOG_ERR("Display not ready");
    }

    hello_world_label = lv_label_create(lv_scr_act());
    measurement_label = lv_label_create(lv_scr_act());

    lv_label_set_text(hello_world_label, "IoT sulari");
    lv_label_set_text(measurement_label, "");

    lv_obj_align(hello_world_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_align(measurement_label, LV_ALIGN_CENTER, 0, 0);

    lv_task_handler();
    display_blanking_off(display_dev);

    while(true)
    {

        sprintf(count_str, "%.02f°C   %.02f%%", temp, humidity);
        lv_label_set_text(measurement_label, count_str);

        lv_task_handler();

        k_msleep(DISPLAY_THREAD_SLEEP_MS);
    }
}

int main(void)
{
    /* Initialize IRS things */
    buttons_init();
    return 0;
}
