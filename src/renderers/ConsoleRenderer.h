#pragma once
#include "Constants.h"
#include "Graphics.h"
#include "renderers/IRenderer.h"
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

/// <summary>
/// provides functionality to render the screen to the console
/// </summary>
class ConsoleRenderer: public IRenderer
{
	public:
	ConsoleRenderer();

	/// <summary>
	/// renders the given pixels to the console
	/// </summary>
	/// <param name="pixels">pixels to render</param>
	void render(const Bitset2D& pixels, const DynamicBitset& screen_symbols, bool force_rerender);

	private:
	/// <summary>
	/// sets the cursor to the top left of the console
	/// </summary>
	void set_cursor_top_left();
	/// <summary>
	/// creates a border for display width
	/// </summary>
	/// <returns>string containing #</returns>
	std::string get_display_border();
};