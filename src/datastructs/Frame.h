#pragma once
#include "datastructs/Bitset2D.h"


struct Frame {
	/// <summary>
	/// bitset describing the pixels of the frame
	/// </summary>
	const Bitset2D& pixels;
	/// <summary>
	/// represents all 15 usable screen symbols (0-14), 15, 16, 17 (^, v, Disp) are reserved for the battery symbol <para/>
	/// also, shift & alpha (0 & 1) will be overwrittern
	/// </summary>
	uint16_t screen_symbols;
	uint32_t corner_x = 0;
	uint32_t corner_y = 0;

	Frame(const Bitset2D& pixels, uint16_t screen_symbols):
		pixels(pixels)
	{
		this->screen_symbols = screen_symbols;
	}
	Frame(const Bitset2D& pixels):
		pixels(pixels)
	{
		this->screen_symbols = 0;
	}
	void set_screen_symbol(uint8_t index, bool value)
	{
		if (value) screen_symbols |= (1 << index);
		else screen_symbols &= ~(1 << index);
	}
	bool get_screen_symbol(uint8_t index) const
	{
		return (screen_symbols >> index) & 1;
	}
};