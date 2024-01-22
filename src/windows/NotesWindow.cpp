#include "windows/NotesWindow.h"
#include "NotesWindow.h"

NotesWindow::NotesWindow()
{
	_text = std::vector<std::string>(1, "");
}

NotesWindow::~NotesWindow()
{
}

Frame NotesWindow::update_window()
{
	if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time = Utils::us_since_boot();
		_show_cursor = !_show_cursor;
	}

	clear_window();
	create_menu();

	_corner_y = _current_page * 4 * _line_height;

	return Frame(get_render_canvas(), _screen_symbols);
}

bool NotesWindow::handle_key_down(KeyPress keypress)
{
	std::string key = Chars::KEY_MAP[keypress.key_keyboard];

	if (TextWindow::handle_key_down(keypress)) return true;

	if (keypress.shift && keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("MODE")) {
		open_save_menu();
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("MODE")) {
		open_load_menu();
	} else if (key == "RETURN") {
		_text.push_back("");
		return true;
	} else if (key == "DEL") {
		remove_char();
		return true;
	} else if (key == "unknown") return false;
	else {
		_text[_text.size() - 1] += key;
		return true;
	}
	return false;
}

void NotesWindow::remove_char()
{
	if (_text.size() < 1) return;

	if (_text[_text.size() - 1].size() < 1 && _text.size() > 1)
		_text.pop_back();
	else if (_text[_text.size() - 1].size() > 0)
		_text[_text.size() - 1].pop_back();
}

void NotesWindow::create_menu()
{
	for (uint32_t i = 0; i < _text.size(); i++) {
		add_to_window(Graphics::create_text(_text[i], Graphics::SYMBOLS_6_HIGH, _text_spacing), 0, 1 + i * _line_height);
	}
	if (_show_cursor) {
		if (_text.size() == 0)
			add_to_window(Bitset2D(2, 9, true), 0, 0);
		else {
			uint16_t cursor_x = Utils::get_string_as_pixel_width(_text.back(), Graphics::SYMBOLS_6_HIGH, _text_spacing);
			uint16_t cursor_y = (_text.size() - 1) * _line_height;

			add_to_window(Bitset2D(2, 9, true), cursor_x, cursor_y);
		}
	}
}

void NotesWindow::open_load_menu()
{
	std::function<void(std::string)> callback = [this](std::string filename) {
		NoteSerializable save_file;
		save_file.read_file("notes", filename);
		_text = save_file.get_text();

		WindowManager::get_instance()->close_window(false);
	};
	{
		std::vector<std::string> files = ISerializable::list_dir("notes");
		_load_menu.options.clear();
		for (int i = 0; i < files.size(); i++) {
			_load_menu.options.push_back(new CallbackMenuOption<std::string>(files[i], files[i], callback));
		}
		WindowManager::get_instance()->add_window(&_load_menu);
		_load_menu.create_menu();
	}
}

void NotesWindow::open_save_menu()
{
	InputWindow::input(
		"Enter filename: ",
		[this](std::string filename) {
			if (filename.rfind(".txt") == std::string::npos) {
				filename += ".txt";
			}
			std::replace(filename.begin(), filename.end(), ' ', '_');

			NoteSerializable save_file = NoteSerializable(_text);
			save_file.write_file("notes", filename);
		});
}