#include "windows/ChatWindow.h"

ChatWindow::~ChatWindow()
{
}

bool ChatWindow::handle_key_down(KeyPress keypress)
{
	std::string key = Chars::KEY_MAP[keypress.key_keyboard];

	if (TextWindow::handle_key_down(keypress)) return true;
	else if (key == "RETURN") {
		add_text("...", false, false, false);
		on_return_key();
		_input = "";
		return true;
	} else if (key == "DEL") {
		if (_input.size() > 0)
			_input.pop_back();
		remove_char();
		return true;
	} else if (key == "unknown") return false;
	else {
		_input += key;
		add_text(key, false, false, false);
		return true;
	}
	return false;
}

void ChatWindow::update_window()
{
	if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time = Utils::us_since_boot();
		_show_cursor = !_show_cursor;
	}

	clear_window();
	create_menu();

	_frame.corner_y = _current_page * 4 * _line_height;
}

void ChatWindow::create_menu()
{
	for (uint32_t i = 0; i < _text.size(); i++) {
		_window.put_chars(0, 1 + i * _line_height, Graphics::SYMBOLS_6_HIGH, _text[i], true);
	}
	if (_show_cursor) {
		if (_text.size() == 0) {
			_window.draw_vertical_line(0, 0, 9, true);
			_window.draw_vertical_line(1, 0, 9, true);
		} else {
			uint16_t cursor_x = Utils::get_string_as_pixel_width(_text.back(), Graphics::SYMBOLS_6_HIGH, 1);
			uint16_t cursor_y = (_text.size() - 1) * _line_height;

			_window.draw_vertical_line(cursor_x, cursor_y, 9, true);
			_window.draw_vertical_line(cursor_x + 1, cursor_y, 9, true);
		}
	}
}

void ChatWindow::add_text(std::string text_to_add, bool keep_words, bool newline, bool leading_space)
{
	std::vector<std::string> words = Utils::split_string(text_to_add, ' ');

	if (newline || _text.size() == 0)
		_text.push_back("");

	if (leading_space)
		_text[_text.size() - 1] += " ";

	if (!keep_words) {
		for (int i = 0; i < text_to_add.size(); i++) {
			if (Utils::get_string_as_pixel_width(_text[_text.size() - 1] + text_to_add[i], Graphics::SYMBOLS_6_HIGH) > SCREEN_WIDTH)
				_text.push_back("");

			if (text_to_add[i] == '\n')
				_text.push_back("");
			else
				_text[_text.size() - 1] += text_to_add[i];
		}
	} else {
		for (int i = 0; i < words.size(); i++) {
			uint32_t word_width = Utils::get_string_as_pixel_width(words[i], Graphics::SYMBOLS_6_HIGH);

			if (Utils::get_string_as_pixel_width(_text[_text.size() - 1], Graphics::SYMBOLS_6_HIGH) + word_width > SCREEN_WIDTH)
				_text.push_back("");

			if (word_width > SCREEN_WIDTH) {
				for (int j = 0; j < words[i].size(); j++) {
					if (Utils::get_string_as_pixel_width(_text[_text.size() - 1] + words[i][j], Graphics::SYMBOLS_6_HIGH) > SCREEN_WIDTH)
						_text.push_back("");

					_text[_text.size() - 1] += words[i][j];
				}
				_text[_text.size() - 1] += " ";
			} else
				_text[_text.size() - 1] += words[i] + " ";
		}
	}

	_current_page = pages_count() - 1;
}

void ChatWindow::remove_char()
{
	if (_text.size() < 1) return;

	if (_text[_text.size() - 1].size() < 1)
		_text.pop_back();

	if (_text.size() < 1 || _text[_text.size() - 1].size() < 1) return;
	_text[_text.size() - 1].pop_back();
}

void ChatWindow::on_return_key()
{
}