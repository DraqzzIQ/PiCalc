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
	FileSelectWindow::select_file("notes", [this](std::string filename) {
		KEY_SET bytes;
		IOController::read_file("notes", filename, &bytes);
		_text.set_key_set(bytes);
	});
}

void NotesWindow::open_save_menu()
{
	InputWindow::input("Filename:", [this](std::string filename) {
		if (filename.rfind(".txt") == std::string::npos) filename += ".txt";
		std::replace(filename.begin(), filename.end(), ' ', '_');
		IOController::write_file("notes", filename, _text.get_raw_bytes());
	});
}