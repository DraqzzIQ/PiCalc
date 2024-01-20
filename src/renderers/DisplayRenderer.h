#pragma once
#ifdef PICO
#include "constant/LCDConstants.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "renderers/IRenderer.h"
#include "utils/Utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>

/// <summary>
/// provides functionality to render to the display
/// </summary>
class DisplayRenderer: public IRenderer
{
	public:
	DisplayRenderer();

	/// <summary>
	/// renders the given frame to the display
	/// </summary>
	/// <param name="frame">frame to render</param>
	void render(const Frame& frame, bool force_rerender);
	/// <summary>
	/// sets the contrast of the lcd
	/// </summary>
	/// <param name="value">0-127</param>
	void set_contrast(uint8_t value);
	/// <summary>
	/// get the current contrast of the lcd
	/// </summary>
	void get_contrast();

	private:
	/// <summary>
	/// clears the display
	/// </summary>
	void clear();
	/// <summary>
	/// sub_addresses for the display chips
	/// </summary>
	uint8_t sub_devices[3] = { A_SUB_ADDRESS_0, A_SUB_ADDRESS_1, A_SUB_ADDRESS_2 };
	/// <summary>
	/// sets the mode of the display
	/// </summary>
	uint8_t set_mode(uint8_t mode, uint8_t status, uint8_t mux_mode, uint8_t command_following);
	/// <summary>
	/// selects the device at the given address
	/// </summary>
	uint8_t select_device(uint8_t addr, uint8_t command_following);
	/// <summary>
	/// accesses the ram at the given address
	/// </summary>
	uint8_t ram_access(uint8_t access_mode, uint8_t row_address, uint8_t command_following);
	/// <summary>
	/// loads the x (column) address
	/// </summary>
	uint8_t load_x_address(uint8_t column_address, uint8_t command_following);
	/// <summary>
	/// reverses the bits in a byte
	/// </summary>
	uint8_t reverse_byte(uint8_t b);
	/// <summary>
	/// current contrast of the display
	/// </summary>
	uint8_t _contrast = 20;

	const std::vector<uint8_t> screen_symbol_positions{ 3, 5, 7, 14, 17, 25, 32, 41, 46, 56, 62, 67, 71, 74, 81, 88, 89, 93 };
};
#endif
