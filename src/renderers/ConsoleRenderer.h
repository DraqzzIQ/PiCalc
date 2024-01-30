#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
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
	/// renders the given frame to the console
	/// </summary>
	/// <param name="frame">frame to render</param>
	void render(const Frame& frame, bool force_rerender) override;

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
