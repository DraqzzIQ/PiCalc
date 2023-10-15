#include "utils/I2CUtils.h"
#ifdef PICO

void I2CUtils::init_i2c()
{
	i2c_init(i2c_default, 100000);
	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

bool I2CUtils::device_availible(uint8_t addr)
{
	uint8_t rxdata = 0;
	int status = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
	return status < 0 ? false : true;
}
#endif
