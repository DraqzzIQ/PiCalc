#pragma once
#include <stdint.h>
/// <summary>
/// KeyPress 
/// </summary>
struct KeyPress
{
	uint8_t key;
	bool shift;
	bool alpha;
};