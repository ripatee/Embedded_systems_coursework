#include <stdio.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/mqtt.h>

#include "sensors.h"
#include "buttons.h"
#include "lte.h"
#include "mqtt_connection.h"

#define SLEEP_TIME_MS	1000

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

static struct mqtt_client mqtt_client;
static struct pollfd fds;

int main(void)
{
	double temp;
	double humidity;
	int err;
	uint32_t connect_attempt = 0;
	char mqtt_msg[256] = "Testing MQTT from nRF9160";

	LOG_INF("Application starting");

	/* Initialising everything */
	sensors_init();
	buttons_init();

	if (lte_modem_configure())
	{
		LOG_ERR("Failed to configure modem");
		return 0;
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

	LOG_INF("MQTT connected");

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

		snprintfcb(mqtt_msg, sizeof(mqtt_msg), 
				   "Temp: %.2fC, Humidity: %.2f%%", temp, humidity);

		LOG_INF("%s", mqtt_msg);

		if (mqtt_data_publish(&mqtt_client, MQTT_QOS_1_AT_LEAST_ONCE,
							  mqtt_msg, sizeof(mqtt_msg)))
		{
			LOG_ERR("Failed to send MQTT message");
		}

		// MQTT related things
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

		k_msleep(SLEEP_TIME_MS);
	}

	LOG_INF("Disconnecting MQTT client");

	err = mqtt_disconnect(&mqtt_client);
	if (err) {
		LOG_ERR("Could not disconnect MQTT client: %d", err);
	}
	goto do_connect;
}
