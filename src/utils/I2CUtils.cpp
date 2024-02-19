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

uint8_t DisplayRenderer::get_contrast()
{
	return _contrast;
}

void I2CUtils::set_contrast(uint8_t value)
{
	_contrast = value;
	uint8_t command[2];
	command[0] = POT_REGISTER_ADDRESS;
	command[1] = value;
	i2c_write_blocking(i2c_default, POT_DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);
}
#endif
