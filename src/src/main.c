#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "sensors.h"
#include "buttons.h"
#include "lte.h"

#define SLEEP_TIME_MS	10000

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

extern struct k_sem lte_connected;

int main(void)
{
	double temp;
	double humidity;

	LOG_INF("Application starting");

	sensors_init();
	buttons_init();

	if (lte_modem_configure())
	{
		LOG_ERR("Failed to configure modem");
	}

	LOG_INF("Connecting to LTE network");

	k_sem_take(&lte_connected, K_FOREVER);

	LOG_INF("Connected to LTE network");

	/* Main loop*/
	while(true)
	{
		temp = get_temperature();
		humidity = get_humidity();

		LOG_DBG("Temp: %.2fC, Humidity: %.2f%%", temp, humidity);

	k_msleep(SLEEP_TIME_MS);
	}
}
