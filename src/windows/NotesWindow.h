#pragma once
#include "io/NoteSerializable.h"
#include "options/CallbackMenuOption.h"
#include "utils/Utils.h"
#include "windows/InputWindow.h"
#include "windows/MenuWindow.h"
#include "windows/TextWindow.h"
#include <functional>

class NotesWindow: public TextWindow
{
	public:
	NotesWindow();
	~NotesWindow();
	Frame update_window();
	bool handle_key_down(KeyPress keypress);

	private:
	/// <summary>
	/// removes the last character of the text
	/// </summary>
	void remove_char();
	/// <summary>
	/// creates the menu out of the text
	/// </summary>
	void create_menu();

	void open_load_menu();
	void open_save_menu();

	uint64_t _last_blink_time = 0;
	bool _show_cursor = false;
	MenuWindow _load_menu = MenuWindow();
};
