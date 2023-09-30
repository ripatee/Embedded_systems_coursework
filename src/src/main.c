#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "sensors.h"
#include "buttons.h"

#define SLEEP_TIME_MS	10000

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

int main(void)
{
	double temp;
	double humidity;

	LOG_INF("Application starting");

	sensors_init();
	buttons_init();

	/* Main loop*/
	while(true)
	{
		temp = get_temperature();
		humidity = get_humidity();

		LOG_DBG("Temp: %.2fC, Humidity: %.2f%%", temp, humidity);

	k_msleep(SLEEP_TIME_MS);
	}
}
