#pragma once
#include "Constants.h"
#include <vector>
#include <string>

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
		/// handles keyboard events
		/// </summary>
		virtual void handle_keyboard_event(int key) = 0;
		/// <summary>
		/// render_plane describing the window
		/// </summary>
		render_plane window;
		/// <summary>
		/// x coordinate of the upper left corner of the part of the canvas that is rendered
		/// </summary>
		int corner_x;
		/// <summary>
		/// y coordinate of the upper left corner of the part of the canvas that is rendered
		/// </summary>
		int corner_y;


		std::vector<bool> screen_symbols;

		/// <summary>
		/// extracts the part of the window that is rendered wich is defined by the corner coordinates and <see cref="SCREEN_WIDTH"/> and <see cref="SCREEN_HEIGHT"/>
		/// </summary>
		/// <returns>canvas to render</returns>
		render_plane get_render_canvas();
		/// <summary>
		/// adds a graphic in form of a render_plane (like text) at given coordinates to the screen
		/// </summary>
		/// <param name="renderplane"></param>
		/// <param name="c_x"></param>
		/// <param name="c_y"></param>
		void add_to_window(render_plane graphic, int c_x, int c_y);
		/// <summary>
		/// clears the window
		/// </summary>
		void clear_window();
		void clear_symbols();

		void change_Symbol(std::string symbol, bool state);
};