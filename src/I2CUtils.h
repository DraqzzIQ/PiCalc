#pragma once
#ifdef PICO
#include "hardware/i2c.h"
#include "pico/stdlib.h"

/// <summary>
/// provides functionality for I2C
/// </summary>
class I2CUtils
{
	public:
	/// <summary>
	/// initializes the I2C bus
	/// </summary>
	static void init_i2c();
	/// <summary>
	/// checks if a device is availible at the given address
	/// </summary>
	static bool device_availible(uint8_t addr);
};
#endif