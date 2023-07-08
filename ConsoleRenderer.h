#pragma once
#include "IRenderer.h"
#include "Constants.h"
#include <iostream>

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
		void render(const render_plane pixels);

	private:
		/// <summary>
		/// clears the console and sets the cursor to the top left
		/// </summary>
		void clear_screen();
		/// <summary>
		/// creates a border for display width
		/// </summary>
		/// <returns>string containing #</returns>
		std::string get_display_border();
};

