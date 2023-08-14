#pragma once
#include <stdint.h>
/// <summary>
/// KeyPress 
/// </summary>
struct KeyPress
{
	uint8_t key;
	uint8_t raw_key;
	bool shift;
	bool alpha;
};