#pragma once
#include <stdint.h>
/// <summary>
/// KeyPress
/// </summary>
struct KeyPress {
	KEY key_calculator;
	KEY key_keyboard;
	KEY key_raw;
	bool shift;
	bool alpha;
};
