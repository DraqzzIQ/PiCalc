#include "renderers/DisplayRenderer.h"
#ifdef PICO

uint64_t DisplayRenderer::_timer = 0;
uint8_t DisplayRenderer::_battery_symbols = 0b11;
const std::vector<uint8_t> DisplayRenderer::screen_symbol_positions{ 3, 5, 7, 14, 17, 25, 32, 41, 46, 56, 62, 67, 71, 74, 81, 88, 89, 93 };

void DisplayRenderer::init()
{
	Utils::sleep_for_ms(1);
	clear();
}

void DisplayRenderer::render(const Frame& frame)
{
	if (_timer + 500000 > Utils::us_since_boot()) {
		_timer = Utils::us_since_boot();
		Utils::update_voltage();
		if (Utils::voltage > 360000) _battery_symbols = 0b11;
		else if (Utils::voltage > 320000) _battery_symbols = 0b10;
		else if (_battery_symbols == 0b00) _battery_symbols = 0b11;
		else _battery_symbols = 0b00;
	}

	// 3 commands + 4 bytes per column
	uint8_t command[387];
	command[0] = select_device(A_SUB_ADDRESS_0, C_COMMAND_FOLLOWING);
	command[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
	command[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

	uint16_t index = 3;
	uint8_t screen_symbol_index = 0;

	uint32_t x_end = frame.corner_x + SCREEN_WIDTH;
	for (uint32_t x = frame.corner_x; x < x_end; x++) {
		std::vector<uint8_t> bytes(4, 0);
		if (x < frame.pixels.width()) bytes = frame.pixels.at(x).get_bytes(frame.corner_y);

		if (x < 82) {
			if (x == screen_symbol_positions[screen_symbol_index] && frame.get_screen_symbol(screen_symbol_index++)) bytes[0] |= 0x80;
		} else if (x == 88) {
			if (_battery_symbols & 0b10) bytes[0] |= 0x80;
		} else if (x == 89) {
			if (_battery_symbols & 0b01) bytes[0] |= 0x80;
		} else if (x == 93 && Utils::charging) bytes[0] |= 0x80;

		for (uint8_t i = 0; i < 4; i++) {
			command[index++] = reverse_byte(bytes[i]);
		}
	}
	i2c_write_blocking(i2c_default, LCD_DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);
}

uint8_t DisplayRenderer::reverse_byte(uint8_t b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

void DisplayRenderer::clear()
{
	uint8_t command[1] = { set_mode(T_ROW_MODE, E_NORMAL_STATUS, M_1_32_MULTIPLEX, C_LAST_COMMAND) };
	i2c_write_blocking(i2c_default, LCD_DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);
}

uint8_t DisplayRenderer::set_mode(uint8_t mode, uint8_t status, uint8_t mux_mode, uint8_t command_following)
{
	return command_following + SET_MODE + mode + status + mux_mode;
}
uint8_t DisplayRenderer::select_device(uint8_t addr, uint8_t command_following)
{
	return command_following + DEVICE_SELECT + addr;
}
uint8_t DisplayRenderer::ram_access(uint8_t access_mode, uint8_t row_address, uint8_t command_following)
{
	return command_following + RAM_ACCESS + access_mode + row_address;
}
uint8_t DisplayRenderer::load_x_address(uint8_t column_address, uint8_t command_following)
{
	return command_following + LOAD_X_ADDRESS + column_address;
}
#endif
