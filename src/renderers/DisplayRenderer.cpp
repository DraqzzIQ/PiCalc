#include "renderers/DisplayRenderer.h"
#ifdef PICO

DisplayRenderer::DisplayRenderer()
{
	Utils::sleep_for_ms(1);
	clear();
	set_contrast(0);
}

void DisplayRenderer::render(const Bitset2D& pixels, const DynamicBitset& screen_symbols, bool force_rerender)
{
	if (!force_rerender && already_rendered(pixels, screen_symbols))
		return;

	// 3 commands + 4 bytes per column
	uint8_t command[387];
	command[0] = select_device(A_SUB_ADDRESS_0, C_COMMAND_FOLLOWING);
	command[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
	command[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

	uint16_t index = 3;
	uint8_t screen_symbol_index = 0;

	for (uint8_t j = 0; j < pixels.width(); j++) {
		std::vector<uint8_t> bytes = pixels[j].get_bytes();

		// comment this
        bytes[3] >>= 1;
        if (bytes[2] & 1) bytes[3] |= 0x80;
        bytes[2] >>= 1;
        if (bytes[1] & 1) bytes[2] |= 0x80;
        bytes[1] >>= 1;
        if (bytes[0] & 1) bytes[1] |= 0x80;
        bytes[0] >>= 1;
        if (j == screen_symbol_positions[screen_symbol_index] && screen_symbols.size() > screen_symbol_index && screen_symbols.at(screen_symbol_index++) == 1) bytes[0] |= 0x80;
        // to here

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

void DisplayRenderer::set_contrast(uint8_t value)
{
	uint8_t command[2];
	command[0] = POT_REGISTER_ADDRESS;
	command[1] = value;
	i2c_write_blocking(i2c_default, POT_DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);
}
#endif
