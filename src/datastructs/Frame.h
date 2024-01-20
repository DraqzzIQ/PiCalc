#pragma once
#include "datastructs/Bitset2D.h"


struct Frame {
	Bitset2D pixels;
	DynamicBitset screen_symbols;

	Frame(const Bitset2D& pixels, const DynamicBitset& screen_symbols)
	{
		this->pixels = pixels;
		this->screen_symbols = screen_symbols;
	}
	Frame()
	{
		this->pixels = Bitset2D();
		this->screen_symbols = DynamicBitset();
	}
};