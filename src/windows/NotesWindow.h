#pragma once
#include "datastructs/Equation.h"
#include "io/NoteSerializable.h"
#include "options/CallbackMenuOption.h"
#include "utils/Utils.h"
#include "windows/InputWindow.h"
#include "windows/MenuWindow.h"
#include <functional>

class NotesWindow: public Window
{
	public:
	NotesWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;
	bool handle_key_up(KeyPress keypress) override;

	private:
	void open_load_menu();
	void open_save_menu();

	Equation _text;

	MenuWindow _load_menu = MenuWindow();
};
