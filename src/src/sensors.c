#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

#include "sensors.h"

#define TMP116_NODE     DT_COMPAT_GET_ANY_STATUS_OKAY(ti_tmp116)
#define SHT4X_NODE      DT_COMPAT_GET_ANY_STATUS_OKAY(sensirion_sht4x)

LOG_MODULE_REGISTER(SENSORS, LOG_LEVEL_ERR);

/* Private data*/
static const struct device *tmp116 = DEVICE_DT_GET(TMP116_NODE);
static const struct device *sht4x  = DEVICE_DT_GET(SHT4X_NODE);

/* Private functions*/

/* Public functions*/

void sensors_init()
{
    if(!device_is_ready(tmp116))
    {
        LOG_ERR("TMP116 is not ready");
        __ASSERT(0, "TMP116 is not ready");
    }

    if(!device_is_ready(sht4x))
    {
        LOG_ERR("SHT4X is not ready");
        __ASSERT(0, "SHT4X is not ready");
    }
}

double get_temperature()
{
    struct sensor_value temperature;

    if (sensor_sample_fetch(tmp116))
    {
        LOG_ERR("Failed to fetch measurements from TMP116");
    }
    
    if (sensor_channel_get(tmp116, SENSOR_CHAN_AMBIENT_TEMP, &temperature))
    {
        LOG_ERR("Failed to get measurements from TMP116");
    }

    return sensor_value_to_double(&temperature);
}

double get_humidity()
{
    struct sensor_value humidity;

    if (sensor_sample_fetch(sht4x))
    {
        LOG_ERR("Failed to fetch measurements from SHT4X");
    }

    if (sensor_channel_get(sht4x, SENSOR_CHAN_HUMIDITY, &humidity))
    {
        LOG_ERR("Failed to get measurements from TMP116");
    }
    
    return sensor_value_to_double(&humidity);
}