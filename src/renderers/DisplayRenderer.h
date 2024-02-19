#pragma once
// TODO: make this work and make battery level showing work
#ifdef PICO
#include "constant/LCDConstants.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "utils/Utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>

/// <summary>
/// provides functionality to render to the display
/// </summary>
class DisplayRenderer:
{
	public:
	static void init();

	/// <summary>
	/// renders the given frame to the display
	/// </summary>
	/// <param name="frame">frame to render</param>
	static void render(const Frame& frame, bool force_rerender);

	private:
	/// <summary>
	/// clears the display
	/// </summary>
	static void clear();
	/// <summary>
	/// sub_addresses for the display chips
	/// </summary>
	static uint8_t sub_devices[3] = { A_SUB_ADDRESS_0, A_SUB_ADDRESS_1, A_SUB_ADDRESS_2 };
	/// <summary>
	/// sets the mode of the display
	/// </summary>
	static uint8_t set_mode(uint8_t mode, uint8_t status, uint8_t mux_mode, uint8_t command_following);
	/// <summary>
	/// selects the device at the given address
	/// </summary>
	static uint8_t select_device(uint8_t addr, uint8_t command_following);
	/// <summary>
	/// accesses the ram at the given address
	/// </summary>
	static uint8_t ram_access(uint8_t access_mode, uint8_t row_address, uint8_t command_following);
	/// <summary>
	/// loads the x (column) address
	/// </summary>
	static uint8_t load_x_address(uint8_t column_address, uint8_t command_following);
	/// <summary>
	/// reverses the bits in a byte
	/// </summary>
	static uint8_t reverse_byte(uint8_t b);
	/// <summary>
	/// current contrast of the display
	/// </summary>
	static uint64_t _timer = 0;
	static uint8_t _battery_symbols = 0b11;

	static const std::vector<uint8_t> screen_symbol_positions{ 3, 5, 7, 14, 17, 25, 32, 41, 46, 56, 62, 67, 71, 74, 81, 88, 89, 93 };
};
#endif
