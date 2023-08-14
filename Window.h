#pragma once
#include "Constants.h"
#include "KeyPress.h"
#include <vector>
#include <string>
#include <stdint.h>

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
		/// handles keydown events
		/// </summary>
		/// <param name="key">key that got pressed</param>
		virtual void handle_key_down(KeyPress keypress);
		/// <summary>
		/// handles keyup events
		/// </summary>
		/// <param name="key">key that got released</param>
		virtual void handle_key_up(KeyPress keypress);
		/// <summary>
		/// calles when window is displayed
		/// </summary>
		virtual void got_focus();
		/// <summary>
		/// called when window is not displayed anymore
		/// </summary>
		virtual void lost_focus();
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
		/// <summary>
		/// saves, which symbols on the lcd should be displayed
		/// </summary>
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
		/// <param name="corner_x"></param>
		/// <param name="corner_y"></param>
		void add_to_window(render_plane graphic, int corner_x, int corner_y);
		/// <summary>
		/// clears the window
		/// </summary>
		void clear_window();
		/// <summary>
		/// clears all on-screen symbols from the lcd
		/// </summary>
		void clear_symbols();
		/// <summary>
		/// changes, whether a symbol shoud be displayed on the LCD
		/// </summary>
		/// <param name="symbol">symbol to change state</param>
		/// <param name="state">state to change symbol to</param>
		void change_symbol(std::string symbol, bool state);
};