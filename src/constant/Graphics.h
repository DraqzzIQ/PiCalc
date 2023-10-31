#pragma once
#include "Chars.h"
#include "constant/Constants.h"
#include "datastructs/Bitset2D.h"
#include <map>
#include <string>
#include <vector>

using FONT = const std::map<uint8_t, Bitset2D>;

/// <summary>
/// provides static graphics to render and related functions
/// </summary>
class Graphics
{
	public:
	Graphics();
	~Graphics();

	/// <summary>
	/// creates a Bitset2D text from string
	/// </summary>
	/// <param name="text">text to be transformed</param>
	/// <param name="table">charset to be used</param>
	/// <param name="spacing">spacing between each char</param>
	/// <returns>converted text</returns>
	static Bitset2D create_text(const std::string& text, FONT& table = SYMBOLS_9_HIGH, const uint16_t spacing = 1);

	static const Bitset2D EMPTY_SCREEN;
	static const Bitset2D LOGO_SCREEN;

	static FONT SYMBOLS_9_HIGH;

	static FONT SYMBOLS_7_HIGH;

	static FONT SYMBOLS_6_HIGH;

	static const std::map<uint8_t, std::vector<uint8_t>> key_text;
	// TODO: enum
	static const std::vector<std::string> SCREEN_SYMBOLS;
};