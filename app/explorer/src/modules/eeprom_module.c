#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/logging/log.h>

#define MODULE eeprom_module

LOG_MODULE_REGISTER(MODULE);

const struct device *eeprom = DEVICE_DT_GET(DT_ALIAS(eeprom_0));





