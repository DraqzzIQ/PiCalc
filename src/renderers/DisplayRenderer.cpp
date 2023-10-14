#include "renderers/DisplayRenderer.h"
#ifdef PICO

DisplayRenderer::DisplayRenderer()
{
	Utils::sleep_for_ms(1);
	clear();
}

void DisplayRenderer::render(const Bitset2D& pixels, const DynamicBitset& screen_symbols, bool force_rerender)
{
	if (!force_rerender && already_rendered(pixels, screen_symbols)) return;

	// DONT FORGET::: only 3 commands when sub device addressess are properly implemented
	// 3  * 3 commands + 4 bytes per column
	uint8_t command[163];
	command[0] = select_device(A_SUB_ADDRESS_0, C_COMMAND_FOLLOWING);
	command[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
	command[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

	uint16_t index = 3;

	for (uint8_t j = 0; j < 40; j++) {
		std::vector<uint8_t> bytes = pixels[j].get_bytes();
		for (uint8_t i = 0; i < 4; i++) { command[index++] = bytes[i]; }
	}
	i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);

	command[0] = select_device(A_SUB_ADDRESS_1, C_COMMAND_FOLLOWING);
	command[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
	command[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

	index = 3;

	for (uint8_t j = 40; j < 80; j++) {
		std::vector<uint8_t> bytes = pixels[j].get_bytes();
		for (uint8_t i = 0; i < 4; i++) { command[index++] = bytes[i]; }
	}

	i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);

	uint8_t command2[67];
	command2[0] = select_device(A_SUB_ADDRESS_2, C_COMMAND_FOLLOWING);
	command2[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
	command2[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

	index = 3;

	for (uint8_t j = 80; j < 96; j++) {
		std::vector<uint8_t> bytes = pixels[j].get_bytes();
		for (uint8_t i = 0; i < 4; i++) { command2[index++] = bytes[i]; }
	}
	i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command2, sizeof(command2), C_LAST_COMMAND);
}


void DisplayRenderer::clear()
{
	uint8_t command[1] = { set_mode(T_ROW_MODE, E_NORMAL_STATUS, M_1_32_MULTIPLEX, false) };
	i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), false);
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
