#pragma once
#include "IRenderer.h"
#include "Constants.h"
#include <iostream>
#include <chrono>
#include <cmath>

/// <summary>
/// provides functionality to render the screen to the console
/// </summary>
class ConsoleRenderer : public IRenderer
{
	public:
		ConsoleRenderer();

		/// <summary>
		/// renders the given pixels to the console
		/// </summary>
		/// <param name="pixels">pixels to render</param>
		void render(const render_plane pixels, std::vector<bool> screenSymbols);

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
		/// <summary>
		/// calculates the fps
		/// </summary>
		/// <returns>fps</returns>
		int calculate_fps();
		/// <summary>
		/// start time of the current frame
		/// </summary>
		clock_t current_ticks;
};

