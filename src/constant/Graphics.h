#pragma once
#include "constant/Constants.h"
#include "datastructs/Bitset2D.h"

using FONT = const std::map<KEY, Bitset2D>;

/// <summary>
/// provides static graphics to render and related functions
/// </summary>
class Graphics
{
	public:
	Graphics();
	~Graphics();

	/// <summary>
	/// creates a Bitset2D text from string<para/>
	/// DEPRECATED: use Bitset2D::put_chars instead
	/// </summary>
	/// <param name="text">text to be transformed</param>
	/// <param name="table">charset to be used</param>
	/// <param name="spacing">spacing between each char</param>
	/// <returns>converted text</returns>
	static Bitset2D create_text(const std::string& text, FONT& table = SYMBOLS_9_HIGH, const uint16_t spacing = 1);
	/// <summary>
	/// creates a Bitset2D text from KEY_SET<para/>
	/// DEPRECATED: use Bitset2D::put_chars instead
	/// </summary>
	/// <param name="text">text to be transformed</param>
	/// <param name="table">charset to be used</param>
	/// <param name="spacing">spacing between each char</param>
	/// <returns>converted text</returns>
	static Bitset2D create_text(const KEY_SET text, FONT& table = SYMBOLS_9_HIGH, const uint16_t spacing = 1);

	static const Bitset2D ORIGINAL_LOGO;

	static const Bitset2D PICALC_LOGO;

	static FONT SYMBOLS_9_HIGH;

	static FONT SYMBOLS_7_HIGH;

	static FONT SYMBOLS_6_HIGH;

	static FONT SYMBOLS_5_HIGH;
};
