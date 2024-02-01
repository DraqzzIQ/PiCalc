#pragma once
#include "datastructs/Bitset2D.h"


struct Frame {
	/// <summary>
	/// bitset describing the pixels of the frame
	/// </summary>
	const Bitset2D& pixels;
	/// <summary>
	/// represents all 15 usable screen symbols (0-14), 15, 16, 17 (^, v, Disp) are reserved for the battery symbol<para/>
	/// also, shift and alpha (0 and 1) will be overwrittern
	/// </summary>
	uint16_t screen_symbols;
	/// <summary>
	/// x coordinate of the top left corner of the frame
	/// </summary>
	uint32_t corner_x = 0;
	/// <summary>
	/// y coordinate of the top left corner of the frame<para/>
	/// IMPORTANT: defaults to 1, as rendering is most efficient if this is 8n+1, can be changed if needed
	/// </summary>
	uint32_t corner_y = 1;

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