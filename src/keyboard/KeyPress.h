#pragma once
#include <stdint.h>
/// <summary>
/// KeyPress
/// </summary>
struct KeyPress {
	uint8_t key_calculator;
	uint8_t key_keyboard;
	uint8_t key_raw;
	bool shift;
	bool alpha;
};
