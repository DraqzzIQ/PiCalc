#pragma once
#include <vector>
#include <map>
#include <string>
#include "Constants.h"
#include "Chars.h"
#include "bitset_2d.h"

/// <summary>
/// provides static graphics to render and related functions
/// </summary>
class Graphics
{
	public:
		Graphics();
		~Graphics();

        /// <summary>
        /// creates a bitset_2d text from string
        /// </summary>
        /// <param name="text">text to be transformed</param>
        /// <param name="table">charset to be used</param>
        /// <param name="spacing">spacing between each char</param>
        /// <returns>converted text</returns>
        static bitset_2d create_text(const std::string& text, const std::map<uint8_t, bitset_2d>& table = SYMBOLS_9_HIGH, const uint16_t spacing = 1);

		static const bitset_2d EMPTY_SCREEN;
		static const bitset_2d LOGO_SCREEN;

        static const std::map<uint8_t, bitset_2d> SYMBOLS_9_HIGH;

		static const std::map<uint8_t, bitset_2d> SYMBOLS_7_HIGH;

        static const std::map<uint8_t, bitset_2d> SYMBOLS_6_HIGH;

        //TODO: enum
        static const std::vector<std::string> SCREEN_SYMBOLS;
};