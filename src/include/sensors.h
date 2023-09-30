#include <zephyr/drivers/sensor.h>
// #include <zephyr/drivers/eeprom.h>
#include <zephyr/drivers/sensor/tmp116.h>
#include <zephyr/drivers/sensor/sht4x.h>

/* Public functions*/
void sensors_init();
double get_temperature();
double get_humidity();