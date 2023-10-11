#include <stdio.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/mqtt.h>
#include <lvgl.h>

#include "sensors.h"
#include "buttons.h"
#include "lte.h"
#include "mqtt_connection.h"
#include "sms_wrapper.h"

#define SLEEP_TIME_MS	10000

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

static struct mqtt_client mqtt_client;
static struct pollfd fds;

int main(void)
{
    double temp, humidity;
    int err;
    uint32_t connect_attempt = 0;
    char mqtt_msg[256];
    int alert_sent = 0;

    const struct device *display_dev;

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev))
    {
        LOG_ERR("Display not ready");
    }


    LOG_INF("Application starting");

    /* Initialising everything */
    sensors_init();
    buttons_init();

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

    /* Main loop*/
    while(true)
    {
        temp = get_temperature();
        humidity = get_humidity();

#if 0 // Used to test SMS sending
        if (alert_sent == 0)
        {
            alert_sent = 1;
            sms_send_temp_alert(temp);
        }
#endif

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

        k_msleep(SLEEP_TIME_MS);

    }

    LOG_INF("Disconnecting MQTT client");

    err = mqtt_disconnect(&mqtt_client);
    if (err) {
        LOG_ERR("Could not disconnect MQTT client: %d", err);
    }
    goto do_connect;
}
