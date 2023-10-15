#pragma once
#include "windows/Window.h"
#include <math.h>

/// <summary>
/// simple text rendering window
/// </summary>
class TextWindow: public Window
{
	public:
	~TextWindow();
	void handle_key_down(KeyPress keypress);
	Bitset2D update_window();
	/// <summary>
	/// container for all text lines
	/// </summary>
	std::vector<std::string> text;
	/// <summary>
	/// spacing between characters
	/// </summary>
	uint8_t text_spacing = 1;
	/// <summary>
	/// scrolls the text up
	/// </summary>
	void scroll_up();
	/// <summary>
	/// scrolls the text down
	/// </summary>
	void scroll_down();
	/// <summary>
	/// creates the menu out of the text
	/// </summary>
	void create_menu();
	/// <summary>
	/// number of pages
	/// </summary>
	const int pages_count();
	/// <summary>
	/// index of currently selected page
	/// </summary>
	int current_page = 0;
	/// <summary>
	/// height of a text line
	/// </summary>
	const int line_height = 8;

	private:
};
