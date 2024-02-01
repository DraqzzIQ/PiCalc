#include "windows/NotesWindow.h"

bool NotesWindow::handle_key_down_special(KeyPress keypress)
{
	if (keypress.key_raw == KEY_MODE) {
		if (keypress.shift) open_save_menu();
		else open_load_menu();
		return true;
	}
	return false;
}

void NotesWindow::open_load_menu()
{
	std::function<void(std::string)> callback = [this](std::string filename) {
		KEY_SET bytes;
		IOController::read_file("notes", filename, &bytes);
		_text.set_key_set(bytes);

		WindowManager::get_instance()->close_window(false);
	};

	std::vector<std::string> files = IOController::list_dir("notes");
	_load_menu.options.clear();
	for (int i = 0; i < files.size(); i++) {
		_load_menu.options.push_back(new CallbackMenuOption<std::string>(files[i], files[i], callback));
	}
	WindowManager::get_instance()->add_window(&_load_menu);
	_load_menu.create_menu();
}

void NotesWindow::open_save_menu()
{
	InputWindow::input(
		"Filename:",
		[this](std::string filename) {
			if (filename.rfind(".txt") == std::string::npos) filename += ".txt";
			std::replace(filename.begin(), filename.end(), ' ', '_');
			IOController::write_file("notes", filename, _text.get_raw_bytes());
		});
}