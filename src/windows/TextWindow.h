#pragma once
#include "utils/Utils.h"
#include "windows/Window.h"
#include <math.h>

/// <summary>
/// simple text rendering window
/// </summary>
class TextWindow: public Window
{
	public:
	~TextWindow();
	bool handle_key_down(KeyPress keypress);
	Frame update_window();

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
	int pages_count() const;

	protected:
	/// <summary>
	/// container for all text lines
	/// </summary>
	std::vector<std::string> _text;
	/// <summary>
	/// index of currently selected page
	/// </summary>
	int _current_page = 0;
	/// <summary>
	/// height of a text line
	/// </summary>
	const int _line_height = 8;
	/// <summary>
	/// spacing between characters
	/// </summary>
	uint8_t _text_spacing = 1;
};
