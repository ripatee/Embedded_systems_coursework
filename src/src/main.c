
// GPIOs
#if 0

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

/* STEP 9 - Increase the sleep time from 100ms to 10 minutes  */
#define SLEEP_TIME_MS   10*60*1000

/* SW0_NODE is the devicetree node identifier for the node with alias "sw0" */
#define SW0_NODE	DT_ALIAS(sw3) 
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

/* LED0_NODE is the devicetree node identifier for the node with alias "led0". */
#define LED0_NODE	DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);


/* STEP 4 - Define the callback function */
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    gpio_pin_toggle_dt(&led);
}
/* STEP 5 - Define a variable of type static struct gpio_callback */
static struct gpio_callback button_cb_data;

void main(void)
{
	int ret;

	if (!device_is_ready(led.port)) {
		return;
	}

	if (!device_is_ready(button.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return;
	}
	/* STEP 3 - Configure the interrupt on the button's pin */
	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE );

	/* STEP 6 - Initialize the static struct gpio_callback variable   */
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin)); 	
	
	/* STEP 7 - Add the callback function by calling gpio_add_callback()   */
	 gpio_add_callback(button.port, &button_cb_data);
	 
	while (1) {
		/* STEP 8 - Remove the polling code */

        k_msleep(SLEEP_TIME_MS);
	}
}
#endif

// I2C, sensors and UART
#if 0
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/drivers/sensor/tmp116.h>
#include <zephyr/drivers/sensor/sht4x.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>

#define TMP116_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(ti_tmp116)
#define TMP116_EEPROM_NODE DT_CHILD(TMP116_NODE, ti_tmp116_eeprom_0)

static uint8_t eeprom_content[EEPROM_TMP116_SIZE];

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET(TMP116_NODE);
	const struct device *const eeprom = DEVICE_DT_GET(TMP116_EEPROM_NODE);
	const struct device *const sht = DEVICE_DT_GET_ANY(sensirion_sht4x);
	struct sensor_value temp_value;
	struct sensor_value hum_value;

	/* offset to be added to the temperature
	 * only supported by TMP117
	 */
	struct sensor_value offset_value;
	int ret;

	__ASSERT(device_is_ready(dev), "TMP116 device not ready");
	__ASSERT(device_is_ready(eeprom), "TMP116 eeprom device not ready");
	__ASSERT(device_is_ready(sht), "SHT4x device is not ready");

	printk("Device %s - %p is ready\n", dev->name, dev);
	printk("Device %s - %p is ready\n", sht->name, sht);

	ret = eeprom_read(eeprom, 0, eeprom_content, sizeof(eeprom_content));
	if (ret == 0) {
		printk("eeprom content %02x%02x%02x%02x%02x%02x%02x%02x\n",
		       eeprom_content[0], eeprom_content[1],
		       eeprom_content[2], eeprom_content[3],
		       eeprom_content[4], eeprom_content[5],
		       eeprom_content[6], eeprom_content[7]);
	} else {
		printk("Failed to get eeprom content\n");
	}

	/*
	 * if an offset of 2.5 oC is to be added,
	 * set val1 = 2 and val2 = 500000.
	 * See struct sensor_value documentation for more details.
	 */
	offset_value.val1 = 0;
	offset_value.val2 = 0;
	ret = sensor_attr_set(dev, SENSOR_CHAN_AMBIENT_TEMP,
			      SENSOR_ATTR_OFFSET, &offset_value);
	if (ret) {
		printk("sensor_attr_set failed ret = %d\n", ret);
		printk("SENSOR_ATTR_OFFSET is only supported by TMP117\n");
	}
	while (1) {
		ret = sensor_sample_fetch(dev);
		if (ret) {
			printk("Failed to fetch measurements (%d)\n", ret);
			return 0;
		}

		ret = sensor_sample_fetch(sht);
		if (ret) {
			printk("Failed to fetch measurements (%d)\n", ret);
			return 0;
		}

		ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP,
					 &temp_value);
		if (ret) {
			printk("Failed to get measurements (%d)\n", ret);
			return 0;
		}
		ret = sensor_channel_get(sht, SENSOR_CHAN_HUMIDITY, &hum_value);
		if (ret) {
			printk("Failed to get measurements (%d)\n", ret);
			return 0;
		}

		printk("temp is %d.%d oC\n", temp_value.val1, temp_value.val2);
		printk("hum is %f \n", sensor_value_to_double(&hum_value));

		k_sleep(K_MSEC(1000));
	}
	return 0;
}

#endif


// LTE 
#if 1
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* STEP 4 - Include the header file of the nRF Modem library and the LTE link controller library */
#include <modem/nrf_modem_lib.h>
#include <modem/lte_lc.h>

/* STEP 5 - Define the semaphore lte_connected */
static K_SEM_DEFINE(lte_connected, 0, 1);

LOG_MODULE_REGISTER(Lesson2_Exercise2, LOG_LEVEL_INF);

/* STEP 7 - Define the event handler for LTE link control */
static void lte_handler(const struct lte_lc_evt *const evt)
{
	switch (evt->type) {
	/* STEP 7.1 - On changed registration status, print status */
	case LTE_LC_EVT_NW_REG_STATUS:
		if ((evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_HOME) &&
			(evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_ROAMING)) {
			break;
		}
		LOG_INF("Network registration status: %s",
				evt->nw_reg_status == LTE_LC_NW_REG_REGISTERED_HOME ?
				"Connected - home network" : "Connected - roaming");
		k_sem_give(&lte_connected);
		break;
	/* STEP 7.2 - On event RRC update, print RRC mode */
	case LTE_LC_EVT_RRC_UPDATE:
		LOG_INF("RRC mode: %s", evt->rrc_mode == LTE_LC_RRC_MODE_CONNECTED ?
				"Connected" : "Idle");
		break;
	default:
		break;
	}
}

/* STEP 6 - Define the function modem_configure() to initialize an LTE connection */
static int modem_configure(void)
{
	int err;

	LOG_INF("Initializing modem library");

	err = nrf_modem_lib_init();
	if (err) {
		LOG_ERR("Failed to initialize the modem library, error: %d", err);
		return err;
	}

	err = lte_lc_init_and_connect_async(lte_handler);
	if (err) {
		LOG_ERR("Modem could not be configured, error: %d", err);
		return err;
	}

	return 0;
}

int main(void)
{
	int err;

	/* STEP 8 - Call modem_configure() to initiate the LTE connection */
	err = modem_configure();
	if (err) {
		LOG_ERR("Failed to configure the modem");
		return 0;
	}

	LOG_INF("Connecting to LTE network");

	/* STEP 9 - Take the semaphore lte_connected */
	k_sem_take(&lte_connected, K_FOREVER);

	LOG_INF("Connected to LTE network");

	return 0;
}
#endif