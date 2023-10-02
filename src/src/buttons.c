#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "buttons.h"
#include "sms_wrapper.h"
#include "sensors.h"

#define SW0_NODE    DT_ALIAS(sw0)
#define SW1_NODE    DT_ALIAS(sw1)
#define SW2_NODE    DT_ALIAS(sw2)
#define SW3_NODE    DT_ALIAS(sw3)

LOG_MODULE_REGISTER(BUTTONS, LOG_LEVEL_DBG);

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

static void button0_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    LOG_INF("Button 0 pressed.");
}

static void button1_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    LOG_INF("Button 1 pressed.");
}

static void button2_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    LOG_INF("Button 2 pressed.");
}

static void button3_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    LOG_INF("Button 3 pressed.");
}

void buttons_init(void)
{
    int ret;

    if (!device_is_ready(button0.port)) {
        return;
    }

    if (!device_is_ready(button1.port)) {
        return;
    }

    if (!device_is_ready(button2.port)) {
        return;
    }

    if (!device_is_ready(button3.port)) {
        return;
    }

    ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

    ret = gpio_pin_configure_dt(&button2, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

    ret = gpio_pin_configure_dt(&button3, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

    ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE );

    gpio_init_callback(&button0_cb_data, button0_cb, BIT(button0.pin)); 	
    gpio_init_callback(&button1_cb_data, button1_cb, BIT(button1.pin)); 	
    gpio_init_callback(&button2_cb_data, button2_cb, BIT(button2.pin)); 	
    gpio_init_callback(&button3_cb_data, button3_cb, BIT(button3.pin)); 	

    gpio_add_callback(button0.port, &button0_cb_data);
    gpio_add_callback(button1.port, &button1_cb_data);
    gpio_add_callback(button2.port, &button2_cb_data);
    gpio_add_callback(button3.port, &button3_cb_data);
}