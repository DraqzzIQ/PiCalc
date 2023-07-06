#pragma once
#include "Constants.h"
#include <vector>

/// <summary>
/// base class for all windows
/// </summary>
class Window
{
	public:
		Window();
		~Window();
		/// <summary>
		/// called when the window gets rerendered
		/// </summary>
		/// <returns>pixels to render</returns>
		virtual render_plane update_window() = 0;
		/// <summary>
		/// canvas describing the window
		/// </summary>
		render_plane pixels;
		/// <summary>
		/// x coordinate of the upper left corner of the part of the canvas that is rendered
		/// </summary>
		int corner_x;
		/// <summary>
		/// y coordinate of the upper left corner of the part of the canvas that is rendered
		/// </summary>
		int corner_y;

		/// <summary>
		/// extracts the part of the canvas that is rendered wich is defined by the corner coordinates and <see cref="SCREEN_WIDTH"/> and <see cref="SCREEN_HEIGHT"/>
		/// </summary>
		/// <returns>pixels to render</returns>
		render_plane get_render_window();
};