#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "datastructs/Frame.h"
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
	/// <returns>Frame to render</returns>
	virtual Frame update_window();
	/// <summary>
	/// handles keydown events
	/// returns true, if the keypress was handled
	/// </summary>
	/// <param name="key">key that got pressed</param>
	virtual bool handle_key_down(KeyPress keypress);
	/// <summary>
	/// handles keyup events
	/// </summary>
	/// <param name="key">key that got released</param>
	virtual bool handle_key_up(KeyPress keypress);
	/// <summary>
	/// calles when window is displayed
	/// </summary>
	virtual void got_focus();
	/// <summary>
	/// called when window is not displayed anymore
	/// </summary>
	virtual void lost_focus();
	/// <summary>
	/// returns the rendered window
	/// </summary>
	Bitset2D get_preview();

	protected:
	/// <summary>
	/// Bitset2D describing the window
	/// </summary>
	Bitset2D _window;
	/// <summary>
	/// x coordinate of the upper left corner of the part of the canvas that is rendered
	/// </summary>
	int _corner_x = 0;
	/// <summary>
	/// y coordinate of the upper left corner of the part of the canvas that is rendered
	/// </summary>
	int _corner_y = 0;
	/// <summary>
	/// saves, which symbols on the lcd should be displayed
	/// </summary>
	DynamicBitset _screen_symbols;
	/// <summary>
	/// extracts the part of the window that is rendered which is defined by the corner coordinates and <see cref="SCREEN_WIDTH"/> and <see cref="SCREEN_HEIGHT"/>
	/// </summary>
	/// <returns>canvas to render</returns>
	Bitset2D get_render_canvas();
	/// <summary>
	/// adds a graphic in form of a Bitset2D (like text) at given coordinates to the screen
	/// </summary>
	void add_to_window(const Bitset2D& graphic, int corner_x, int corner_y);
	/// <summary>
	/// put text on the screen
	/// </summary>
	void put_text(KEY_SET text, FONT font, int corner_x, int corner_y);
	/// <summary>
	/// put text on the screen
	/// </summary>
	void put_text(std::string text, FONT font, int corner_x, int corner_y);
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
