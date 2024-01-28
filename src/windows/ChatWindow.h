#pragma once
#include "utils/Utils.h"
#include "windows/NotesWindow.h"

class ChatWindow: public NotesWindow
{
	public:
	~ChatWindow();
	bool handle_key_down(KeyPress keypress) override;
	void update_window() override;
	/// <summary>
	/// splits a string into multiple lines fitting the screen
	/// </summary>
	/// <param name="text_to_add">text to add to the screen</param>
	/// <param name="keep_words">if true will try to not split words</param>
	/// <param name="newline"if a newline should be inserted</param>
	void add_text(std::string text_to_add, bool keep_words = true, bool newline = false, bool leading_space = false);

	private:
	/// <summary>
	/// removes the last character of the text
	/// </summary>
	void remove_char();
	/// <summary>
	/// creates the menu out of the text
	/// </summary>
	void create_menu();

	uint64_t _last_blink_time = 0;
	bool _show_cursor = false;

	protected:
	std::string _input;
	virtual void on_return_key();
};
