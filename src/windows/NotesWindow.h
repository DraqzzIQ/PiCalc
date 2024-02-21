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
	bool handle_key_down_special(KeyPress keypress) override
	{
		if (keypress.key_raw == KEY_MODE) {
			if (keypress.shift) InputWindow::input(_filename.empty() ? "Filename:" : "Filename:\n(or empty)", save_callback, !_filename.empty());
			else FileSelectWindow::select_file("notes", load_callback);
			return true;
		}
		return false;
	};

	private:
	std::function<void(std::string)> save_callback = [this](std::string filename) {
		if (filename.empty()) {
			IOController::write_file("notes", _filename, _text.get_raw_bytes());
			return;
		}
		if (filename.rfind(".txt") == std::string::npos) filename += ".txt";
		std::replace(filename.begin(), filename.end(), ' ', '_');
		IOController::write_file("notes", filename, _text.get_raw_bytes());
		_filename = filename;
	};

	std::function<void(std::string)> load_callback = [this](std::string filename) {
		KEY_SET bytes;
		IOController::read_file("notes", filename, &bytes);
		_text.set_key_set(bytes);
		_filename = filename;
	};

	MenuWindow _load_menu = MenuWindow();
	std::string _filename = "";
};
