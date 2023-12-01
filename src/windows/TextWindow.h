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
	int pages_count() const;
	/// <summary>
	/// index of currently selected page
	/// </summary>
	int current_page = 0;
	/// <summary>
	/// height of a text line
	/// </summary>
	const int line_height = 8;
	/// <summary>
	/// splits a string into multiple lines fitting the screen
	/// </summary>
	/// <param name="text_to_add">text to add to the screen</param>
	/// <param name="keep_words">if true will try to not split words</param>
	/// <param name="newline"if a newline should be inserted</param>
	void add_text(std::string text_to_add, bool keep_words = true, bool newline = false, bool leading_space = false);
	/// <summary>
	/// removes the last character of the text
	/// </summary>
	void remove_chars();

	private:
	uint64_t _last_blink_time = 0;
	bool _show_cursor = false;

	protected:
	std::string _input;
	virtual void on_return_key();
};
