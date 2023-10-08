#define DT_DRV_COMPAT waveshare_epd2in9v2

#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/byteorder.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(epd_2in9_v2, CONFIG_EPD_2IN9_V2_LOG_LEVEL);

extern const uint8_t _WF_PARTIAL_2IN9[];
extern const uint8_t WS_20_30[];
extern const unsigned char Gray4[];

#define HIGH    1
#define LOW     0

#define EPD_2IN9_V2_WIDTH       128
#define EPD_2IN9_V2_HEIGHT      296

typedef enum {
    CMD = 0,
    DATA = 1
} send_type;

struct epd_2in9_v2_data {
    const struct device *dev;
};

struct epd_2in9_v2_config {
    struct spi_dt_spec bus;
    struct gpio_dt_spec cs_gpio;
    struct gpio_dt_spec rst_gpio;
    struct gpio_dt_spec busy_gpio;
    struct gpio_dt_spec dc_gpio;
};

static void epd_2in9_v2_reset(const struct device *dev)
{
    const struct epd_2in9_v2_config *config = dev->config;
    int err;

    err = gpio_pin_set_dt(&config->rst_gpio, HIGH);
    if (err)
    {
        LOG_ERR("Failed to set RST pin high");
    }

    k_msleep(10);
    
    err = gpio_pin_set_dt(&config->rst_gpio, LOW);
    if (err)
    {
        LOG_ERR("Failed to set RST pin low");
    }

    k_msleep(2);

    err = gpio_pin_set_dt(&config->rst_gpio, HIGH);
    if (err)
    {
        LOG_ERR("Failed to set RST pin high");
    }

    k_msleep(10);
}

static void send(const struct device *dev, uint8_t val, send_type send_type)
{
    int err;
    const struct epd_2in9_v2_config *config = dev->config;

    // Set display DC pin according are we sending a command or data to display
    // The only difference between sending command or data is the value of the DC pin
    // LOW for command and HIGH for data
    err = gpio_pin_set_dt(&config->dc_gpio, send_type);
    if (err)
    {
        LOG_ERR("Display DC set failed");
    }

    // Set SPI CS pin low (active low)
    err = gpio_pin_set_dt(&config->cs_gpio, LOW);
    if (err)
    {
        LOG_ERR("SPI CS set failed");
    }

    // Initialize and set SPI TX buffers
    uint8_t buf = val;
    const struct spi_buf tx_buf = 
    {
        .buf = &buf,
        .len = 1,
    };
    const struct spi_buf_set tx = 
    {
        .buffers = &tx_buf,
        .count = 1,
    };

    // Do the actual SPI write
    err = spi_write_dt(&config->bus, &tx);
    if (err)
    {
        LOG_ERR("Failed to send data on SPI write");
    }

    // Set CS pin high (active low)
    err = gpio_pin_set_dt(&config->cs_gpio, HIGH);
    if (err)
    {
        LOG_ERR("SPI CS set to 1 (active low) failed");
    }
}

static void read_busy(const struct device *dev)
{
    const struct epd_2in9_v2_config *config = dev->config;

    LOG_DBG("EPD busy");

    while(1)
    {
        if(gpio_pin_get_dt(&config->busy_gpio) == LOW)
        {
            break;
        }
        k_msleep(50);
    }
    k_msleep(50);

    LOG_DBG("EPD busy released");
}

static void send_lut(const struct device *dev, uint8_t *lut)
{
    uint8_t count;
    send(dev, 0x32, CMD);
    for (count = 0; count<153; count++)
    {
        send(dev, lut[count], DATA);
    }
    read_busy(dev);
}

static void send_lut_by_host(const struct device *dev, uint8_t *lut)
{
    send_lut(dev, (uint8_t *)lut);  // LUT
    send(dev, 0x3f, CMD);
    send(dev, *(lut+153), DATA);
    send(dev, 0x3, CMD);            // Gate voltage
    send(dev, *(lut+154), DATA);
    send(dev, 0x04, CMD);           // Source voltage
    send(dev, *(lut+155), DATA);	// VSH
	send(dev, *(lut+156), DATA);	// VSH2
	send(dev, *(lut+157), DATA);	// VSL
	send(dev, 0x2c, CMD);		    // VCOM
	send(dev, *(lut+158), DATA);

}

static void epd_2in9_v2_turn_on_display(const struct device *dev)
{
    send(dev, 0x22, CMD);   // Display Update Control
    send(dev, 0xc7, DATA);
    send(dev, 0x20, CMD);   // Activate Display Update Sequence
    read_busy(dev);
}

static void epd_2in9_v2_turn_on_display_partial(const struct device *dev)
{
    send(dev, 0x22, CMD);   // Display Update Control
    send(dev, 0x0F, DATA);
    send(dev, 0x20, CMD);   // Activate Display Update Sequence
    read_busy(dev);
}

static void epd_2in9_v2_SetWindows(const struct device *dev, uint16_t Xstart, 
                                   uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    send(dev, 0x44, CMD); // SET_RAM_X_ADDRESS_START_END_POSITION
    send(dev, (Xstart>>3) & 0xFF, DATA);
    send(dev, (Xend>>3) & 0xFF, DATA);
	
    send(dev, 0x45, CMD); // SET_RAM_Y_ADDRESS_START_END_POSITION
    send(dev, Ystart & 0xFF, DATA);
    send(dev, (Ystart >> 8) & 0xFF, DATA);
    send(dev, Yend & 0xFF, DATA);
    send(dev, (Yend >> 8) & 0xFF, DATA);
}

static int epd_2in9_v2_init(const struct device *dev)
{
    struct epd_2in9_v2_data *data = dev->data;
    const struct epd_2in9_v2_config *config = dev->config;
    int err = 0;
    
    // Check that SPI and all individual pins are ready
    if(!spi_is_ready_dt(&config->bus))
    {
        LOG_ERR("SPI device not ready");
        return -ENODEV;
    }

    if(!device_is_ready(config->cs_gpio.port))
    {
        LOG_ERR("SPI CS device not ready");
        return -ENODEV;
    }

    if(!device_is_ready(config->rst_gpio.port))
    {
        LOG_ERR("Display RST gpio device not ready");
        return -ENODEV;
    }

    if(!device_is_ready(config->busy_gpio.port))
    {
        LOG_ERR("Display BUSY gpio device not ready");
        return -ENODEV;
    }

    if(!device_is_ready(config->dc_gpio.port))
    {
        LOG_ERR("Display DC gpio device not ready");
        return -ENODEV;
    }

    return err;
}

void epd_2in9_v2_sleep (dev)
{
    send(dev, 0x10, CMD);
    send(dev, 0x01, DATA);
    k_msleep(100);
}

static const struct display_driver_api epd_2in9_v2_driver_api = {
    .blanking_on        = NULL,
    .blanking_off       = NULL,
    .write              = NULL,
    .read               = NULL,
    .get_framebuffer    = NULL,
    .set_brightness     = NULL,
    .set_contrast       = NULL,
    .get_capabilities   = NULL,
    .set_pixel_format   = NULL,
    .set_orientation    = NULL,
};

#define EPD_2IN9_V2_DEFINE(n)						            \
    static struct epd_2in9_v2_data data##n;				        \
                                                                \
    static const struct epd_2in9_v2_config config##n = {		\
        .bus = {						                        \
            .bus = DEVICE_DT_GET(DT_INST_BUS(n)),		        \
            .config = {					                        \
                .frequency = DT_INST_PROP(n,		            \
                              spi_max_frequency),               \
                .operation = SPI_WORD_SET(8) |		            \
                         SPI_TRANSFER_MSB |		                \
                         SPI_MODE_CPOL | SPI_MODE_CPHA,         \
                .slave = DT_INST_REG_ADDR(n),		            \
            },						                            \
        },	                                                    \
        .cs_gpio = SPI_CS_GPIOS_DT_SPEC_GET(DT_DRV_INST(n)),	\
        .rst_gpio = GPIO_DT_SPEC_INST_GET(n, rst_gpios),        \
        .busy_gpio = GPIO_DT_SPEC_INST_GET(n, busy_gpios),      \
        .dc_gpio = GPIO_DT_SPEC_INST_GET(n, dc_gpios),          \
                                                                \
    };								                            \
                                                                \
    DEVICE_DT_INST_DEFINE(n, epd_2in9_v2_init, NULL, &data##n, &config##n,     \
                  POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,	       \
                  &epd_2in9_v2_driver_api);

DT_INST_FOREACH_STATUS_OKAY(EPD_2IN9_V2_DEFINE)