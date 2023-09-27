#pragma once
#include "Constants.h"
#include "Chars.h"
#include <vector>
#include <map>
#include <string>
#include <stdint.h>

/// <summary>
/// provides static graphics to render and related functions
/// </summary>
class Graphics
{
	public:
		Graphics();
		~Graphics();

        /// <summary>
        /// creates a render_plane text from string
        /// </summary>
        /// <param name="text">text to be transformed</param>
        /// <param name="table">charset to be used</param>
        /// <param name="spacing">spacing between each char</param>
        /// <returns>converted text</returns>
        static render_plane create_text(const std::string text, std::map<uint8_t, render_plane> table = SYMBOLS_9_HIGH, int spacing = 1);
        /// <summary>
        /// creates a render_plane text from wstring
        /// </summary>
        /// <param name="text">text to be transformed</param>
        /// <param name="table">charset to be used</param>
        /// <param name="spacing">spacing between each char</param>
        /// <returns>converted text</returns>
        static render_plane create_text(const std::wstring text, std::map<uint8_t, render_plane> table = SYMBOLS_9_HIGH, int spacing = 1);

		static const render_plane EMPTY_SCREEN;
		static const render_plane LOGO_SCREEN;

        static const std::map<uint8_t, render_plane> SYMBOLS_9_HIGH;

		static const std::map<uint8_t, render_plane> SYMBOLS_7_HIGH;

        static const std::map<uint8_t, render_plane> SYMBOLS_6_HIGH;

        //TODO: enum
        static const std::vector<std::string> SCREEN_SYMBOLS;
};