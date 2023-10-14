#pragma once
#include "Constants.h"
#include "Graphics.h"
#include "keyboard/KeyPress.h"
#include <algorithm>
#include <stdint.h>
#include <string>
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
	virtual Bitset2D update_window();
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
	/// Bitset2D describing the window
	/// </summary>
	Bitset2D window;
	/// <summary>
	/// x coordinate of the upper left corner of the part of the canvas that is rendered
	/// </summary>
	int corner_x = 0;
	/// <summary>
	/// y coordinate of the upper left corner of the part of the canvas that is rendered
	/// </summary>
	int corner_y = 0;
	/// <summary>
	/// saves, which symbols on the lcd should be displayed
	/// </summary>
	DynamicBitset screen_symbols;
	/// <summary>
	/// extracts the part of the window that is rendered wich is defined by the corner coordinates and <see cref="SCREEN_WIDTH"/> and <see cref="SCREEN_HEIGHT"/>
	/// </summary>
	/// <returns>canvas to render</returns>
	Bitset2D get_render_canvas();
	/// <summary>
	/// adds a graphic in form of a Bitset2D (like text) at given coordinates to the screen
	/// </summary>
	/// <param name="renderplane"></param>
	/// <param name="corner_x"></param>
	/// <param name="corner_y"></param>
	void add_to_window(const Bitset2D& graphic, int corner_x, int corner_y);
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
	/// <summary>
	/// scrolls the window to the left
	/// </summary>
	void scroll_left();
	/// <summary>
	/// scrolls the window to the right
	/// </summary>
	void scroll_right();
};