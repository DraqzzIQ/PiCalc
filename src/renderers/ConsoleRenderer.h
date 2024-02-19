#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "datastructs/Frame.h"
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

/// <summary>
/// provides functionality to render the screen to the console
/// </summary>
class ConsoleRenderer
{
	public:
	static void init();
	/// <summary>
	/// renders the given frame to the console
	/// </summary>
	/// <param name="frame">frame to render</param>
	static void render(const Frame& frame);

	private:
	/// <summary>
	/// sets the cursor to the top left of the console
	/// </summary>
	static void set_cursor_top_left();
	/// <summary>
	/// creates a border for display width
	/// </summary>
	/// <returns>string containing #</returns>
	static std::string get_display_border();

	static const std::vector<std::string> SCREEN_SYMBOLS;
};
