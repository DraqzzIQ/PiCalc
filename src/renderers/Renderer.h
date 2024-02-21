#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "datastructs/Frame.h"
#include <algorithm>
#include <iostream>

#ifdef PICO
#include "constant/LCDConstants.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "utils/Utils.h"
#include <cmath>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

/// <summary>
/// provides functionality to render the screen to the console
/// </summary>
class Renderer
{
	public:
	/// <summary>
	/// initializes the renderer
	/// </summary>
	static void init();
	/// <summary>
	/// renders the given frame
	/// </summary>
	/// <param name="frame">frame to render</param>
	static void render(const Frame& frame);

	private:
#ifdef PICO
	/// <summary>
	/// clears the display
	/// </summary>
	static void clear();
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
	static uint64_t _timer;
	/// <summary>
	/// which symbols for battery and charging are displayed
	/// </summary>
	static uint8_t _battery_symbols;
	/// <summary>
	/// the x-coordinates at which the screen symbols are displayed
	/// </summary>
	static const std::vector<uint8_t> screen_symbol_positions;
#else
	/// <summary>
	/// sets the cursor to the top left of the console
	/// </summary>
	static void set_cursor_top_left();
	/// <summary>
	/// creates a border for display width
	/// </summary>
	/// <returns>string containing #</returns>
	static std::string get_display_border();
	/// <summary>
	/// string representations of the screen symbols
	/// </summary>
	static const std::vector<std::string> SCREEN_SYMBOLS;
#endif
};
