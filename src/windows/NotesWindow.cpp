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
	else if (key == "RETURN") {
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