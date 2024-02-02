#pragma once
#include "constant/Chars.h"
#include "datastructs/Equation.h"
#include "io/IOController.h"
#include "options/CallbackMenuOption.h"
#include "utils/Utils.h"
#include "windows/FileSelectWindow.h"
#include "windows/InputWindow.h"
#include "windows/MenuWindow.h"
#include "windows/TextWindow.h"
#include <functional>

class NotesWindow: public TextWindow
{
	protected:
	bool handle_key_down_special(KeyPress keypress) override;

	private:
	void open_load_menu();
	void open_save_menu();
	MenuWindow _load_menu = MenuWindow();
};
