#pragma once
#include "Constants.h"
#include "SpecialChars.h"
#include <vector>
#include <map>
#include <string>
#include "SpecialChars.h"

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
        static render_plane create_text(const std::string text, std::map<wchar_t, render_plane> table = SYMBOLS_9_HIGH, int spacing = 1);
        /// <summary>
        /// creates a render_plane text from wstring
        /// </summary>
        /// <param name="text">text to be transformed</param>
        /// <param name="table">charset to be used</param>
        /// <param name="spacing">spacing between each char</param>
        /// <returns>converted text</returns>
        static render_plane create_text(const std::wstring text, std::map<wchar_t, render_plane> table = SYMBOLS_9_HIGH, int spacing = 1);

		static inline const render_plane EMPTY_SCREEN = render_plane(SCREEN_WIDTH, std::vector<bool>(SCREEN_HEIGHT, false));
		static inline const render_plane LOGO_SCREEN = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
		static inline const std::map<wchar_t, render_plane> SYMBOLS_9_HIGH{
			{'A', {{0, 0, 0, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1}}},
			{'B', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 0, 1, 1, 1, 0}}},
            {'C', {{0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0, 1, 0}}},
            {'D', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0}}},
            {'E', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}}},
            {'F', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'G', {{0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 1, 1, 1, 0}}},
            {'H', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}}},
            {'I', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'J', {{0, 0, 0, 0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'K', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 1, 1}}},
            {'L', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}}},
            {'M', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}}},
            {'N', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}}},
            {'O', {{0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 1, 0}}},
            {'P', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 0, 0}}},
            {'Q', {{0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 1, 0, 1}}},
            {'R', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 1, 1, 0}, {0, 1, 1, 1, 0, 0, 0, 0, 1}}},
            {'S', {{0, 1, 1, 1, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 1, 1, 0}}},
            {'T', {{1, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'U', {{1, 1, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 0}}},
            {'V', {{1, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 0, 0, 0, 0}}},
            {'W', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}}},
            {'X', {{1, 1, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 1, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 1, 1, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 1, 1}}},
            {'Y', {{1, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0, 0}}},
            {'Z', {{1, 0, 0, 0, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 1, 1, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 1, 1, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 0, 0, 0, 1}}},
            {'a', {{0, 0, 0, 1, 0, 0, 1, 1, 0}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 1, 0, 0, 1, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1}}},
            {'b', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1, 0, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 1, 1, 0}}},
            {'c', {{0, 0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 0, 0, 0, 1, 0}}},
            {'d', {{0, 0, 0, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}}},
            {'e', {{0, 0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 1, 1, 1, 0, 1, 0}}},
            {'f', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'g', {{0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 0, 1}, {0, 0, 1, 1, 1, 1, 1, 1, 0}}},
            {'h', {{1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1, 1}}},
            {'i', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'j', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 1, 1, 1, 1, 1, 0}}},
            {'k', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 1, 1}}},
            {'l', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'m', {{0, 0, 0, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1, 1}}},
            {'n', {{0, 0, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1}}},
            {'o', {{0, 0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 1, 1, 1, 0}}},
            {'p', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 1, 1, 0, 0, 0}}},
            {'q', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1}}},
            {'r', {{0, 0, 0, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}}},
            {'s', {{0, 0, 0, 1, 1, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 1, 0, 0, 1, 1, 0}}},
            {'t', {{0, 0, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1, 0}}},
            {'u', {{0, 0, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 1, 1}}},
            {'v', {{0, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0, 0}}},
            {'w', {{0, 0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 1, 1, 1, 0}}},
            {'x', {{0, 0, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 1}}},
            {'y', {{0, 0, 1, 1, 1, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 1, 1, 1, 1, 1, 1, 0}}},
            {'z', {{0, 0, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 0, 0, 0, 1, 1}, {0, 0, 0, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 1, 0, 0, 1}, {0, 0, 0, 1, 1, 0, 0, 0, 1}}},
            {'0', {{0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1, 1, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 1, 1, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 1, 0}}},
            {'1', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'2', {{0, 1, 0, 0, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 0, 1}}},
            {'3', {{0, 1, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 0, 1, 1, 1, 0}}},
            {'4', {{0, 0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 1, 1, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 1, 0, 1}}},
            {'5', {{1, 1, 1, 1, 1, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 1, 1, 1, 0}}},
            {'6', {{0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 1, 1, 0}}},
            {'7', {{1, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0, 0}}},
            {'8', {{0, 1, 1, 1, 0, 1, 1, 1, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 0, 1, 1, 1, 0}}},
            {'9', {{0, 1, 1, 1, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 1, 0}}},
            {'+', {{0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}}},
            {'-', {{0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}}},
            {'/', {{0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}}},
            {'*', {{0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 0}}},
            {'=', {{0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 1, 0, 0, 0}}},
            {'(', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {')', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'[', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {']', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {' ', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'.', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {',', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {';', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0, 1}, {0, 1, 1, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {':', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'!', {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}},
            {'?', {{0, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1, 1, 0, 1}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 0, 0}}},
		    {'#', {{0, 0, 1, 0, 0, 0, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0, 1, 0, 0}}},
            {'|', {{1, 1, 1, 1, 1, 1, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 0, 1, 1}}},
            {'%', {{0, 0, 1, 1, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 1, 1}}},
            {PI, {{0, 0, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 1}}},
            {SCRIPT_SMALL_E, {{0, 0, 0, 0, 1, 1, 1, 1, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 1, 0, 0, 0, 1, 0}}},
		};

		static inline const std::map<wchar_t, render_plane> SYMBOLS_7_HIGH{
            {'A', {{0, 0, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 1, 0, 0}, {1, 0, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 1}}},
            {'B', {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {0, 1, 1, 0, 1, 1, 0}}},
            {'C', {{0, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0}}},
            {'D', {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 0, 0}}},
            {'E', {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}}},
            {'F', {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}}},
            {'G', {{0, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 1, 0, 1}, {0, 1, 0, 0, 1, 1, 0}}},
            {'H', {{1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1}}},
		    {'I', {{0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0}}},
            {'J', {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0}}},
            {'K', {{1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0}, {0, 1, 0, 0, 1, 0, 0}, {1, 0, 0, 0, 0, 1, 1}}},
            {'L', {{1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1}}},
            {'M', {{1, 1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1}}},
            {'N', {{1, 1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1}}},
            {'O', {{0, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 0}}},
            {'P', {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0}}},
            {'Q', {{0, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 0, 1}}},
            {'R', {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 1, 0, 0}, {1, 0, 0, 1, 0, 1, 0}, {0, 1, 1, 0, 0, 0, 1}}},
            {'S', {{0, 1, 1, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 1, 1, 0}}},
            {'T', {{1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}}},
            {'U', {{1, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 0}}},
            {'V', {{1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 1, 1, 0, 0}, {1, 1, 1, 0, 0, 0, 0}}},
            {'W', {{1, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 0, 0}}},
            {'X', {{1, 1, 0, 0, 0, 1, 1}, {0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 1, 0, 0}, {1, 1, 0, 0, 0, 1, 1}}},
            {'Y', {{1, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0}}},
            {'Z', {{1, 0, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 0, 1}}},
		};

        static inline const std::map<wchar_t, render_plane> SYMBOLS_6_HIGH{
            {'A', {{0, 0, 1, 1, 1, 1}, {0, 1, 0, 1, 0, 0}, {1, 0, 0, 1, 0, 0}, {0, 1, 0, 1, 0, 0}, {0, 0, 1, 1, 1, 1}}},
            {'B', {{1, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 0}}},
            {'C', {{0, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 0}}},
            {'D', {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 0}, {0, 0, 1, 1, 0, 0}}},
            {'E', {{1, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 1}}},
            {'F', {{1, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0}}},
            {'G', {{0, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 1}, {0, 1, 0, 1, 1, 0}}},
            {'H', {{1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1}}},
            {'I', {{0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}}},
            {'J', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0}}},
            {'K', {{1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0}, {0, 0, 1, 1, 0, 0}, {0, 1, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 1}}},
            {'L', {{1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}}},
            {'M', {{1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0}, {0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1}}},
            {'N', {{1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0}, {1, 1, 1, 1, 1, 1}}},
            {'O', {{0, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 0}}},
            {'P', {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0}, {1, 0, 0, 1, 0, 0}, {1, 0, 0, 1, 0, 0}, {0, 1, 1, 0, 0, 0}}},
            {'Q', {{0, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 0, 1}}},
            {'R', {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0}, {1, 0, 0, 1, 0, 0}, {1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1}}},
            {'S', {{0, 1, 0, 0, 1, 0}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 1}, {0, 1, 0, 0, 1, 0}}},
            {'T', {{1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}}},
            {'U', {{1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 0}}},
            {'V', {{1, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 0}, {1, 1, 1, 0, 0, 0}}},
            {'W', {{1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 1}, {0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 0, 0}}},
            {'X', {{1, 0, 0, 0, 1, 1}, {0, 1, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 1, 0, 1, 0, 0}, {1, 0, 0, 0, 1, 1}}},
            {'Y', {{1, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1}, {0, 0, 1, 0, 0, 0}, {1, 1, 0, 0, 0, 0}}},
            {'Z', {{1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 1, 0, 0, 0, 1}}},
            {'a', {{0, 0, 0, 0, 1, 0}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 0, 1, 1, 1, 1}}},
            {'b', {{1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 0, 1, 1, 1, 0}}},
            {'c', {{0, 0, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0}}},
            {'d', {{0, 0, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 1}, {1, 1, 1, 1, 1, 1}}},
            {'e', {{0, 0, 1, 1, 1, 0}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 0, 1, 1, 0, 0}}},
            {'f', {{0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {'g', {{0, 0, 1, 0, 0, 0}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 1, 1, 1, 0}}},
            {'h', {{1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1}}},
            {'i', {{0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 1}, {1, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}}},
            {'j', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 1}, {1, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0}}},
            {'k', {{0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 0}, {0, 1, 0, 0, 0, 1}}},
            {'l', {{0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}}},
            {'m', {{0, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1}}},
            {'n', {{0, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1}}},
            {'o', {{0, 0, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 0, 1, 1, 1, 0}}},
            {'p', {{0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 1, 0}, {0, 1, 0, 0, 1, 0}, {0, 0, 1, 1, 0, 0}}},
            {'q', {{0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0}, {0, 1, 0, 0, 1, 0}, {0, 1, 0, 1, 0, 0}, {0, 1, 1, 1, 1, 1}}},
            {'r', {{0, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0}}},
            {'s', {{0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 0, 1, 0}}},
            {'t', {{0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0}}},
            {'u', {{0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 1}}},
            {'v', {{0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 0}}},
            {'w', {{0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 1, 1, 1, 0}}},
            {'x', {{0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 0}, {0, 0, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 1}}},
            {'y', {{0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 1}, {0, 1, 1, 1, 1, 0}}},
            {'z', {{0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 1}, {0, 1, 0, 1, 0, 1}, {0, 1, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 1}}},
            {'0', {{0, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 0}}},
            {'1', {{0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}}},
            {'2', {{0, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 1}}},
            {'3', {{0, 1, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 0}}},
            {'4', {{0, 0, 0, 1, 1, 0}, {0, 0, 1, 0, 1, 0}, {0, 1, 0, 0, 1, 0}, {1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0}}},
            {'5', {{1, 1, 1, 0, 1, 0}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 1, 0}}},
            {'6', {{0, 0, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {0, 0, 0, 1, 1, 0}}},
            {'7', {{1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {1, 0, 1, 1, 0, 0}, {1, 1, 0, 0, 0, 0}}},
            {'8', {{0, 1, 0, 1, 1, 0}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {1, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 0}}},
            {'9', {{0, 1, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 1, 0}, {0, 1, 1, 1, 0, 0}}},
            {'+', {{0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}, {0, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}}},
            {'-', {{0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}}},
            {'*', {{0, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 1, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 0}, {0, 1, 0, 0, 0, 1}}},
            {'/', {{0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}, {0, 1, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0}}},
            {'=', {{0, 0, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 0}}},
            {'(', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}}},
            {')', {{0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {'[', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}}},
            {']', {{0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {' ', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {'.', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {',', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {';', {{0, 0, 0, 0, 0, 0}, {1, 1, 0, 1, 0, 1}, {1, 1, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {':', {{0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 1, 1}, {0, 1, 1, 0, 1, 1}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {'!', {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 1}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}},
            {'?', {{0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0}}},
            {'#', {{0, 1, 0, 0, 1, 0}, {1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 1, 0}, {1, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 1, 0}}},
            {'|', {{1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}}},
            {'%', {{0, 1, 1, 0, 0, 1}, {0, 1, 1, 0, 1, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 1}, {0, 1, 0, 0, 1, 1}}},
            {PI, {{0, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1}, {0, 1, 0, 0, 1, 0}}},
            {SCRIPT_SMALL_E, {{0, 0, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 1, 0}}},
        };
};