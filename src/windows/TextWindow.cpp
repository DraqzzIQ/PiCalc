#include "windows/TextWindow.h"

TextWindow::~TextWindow() {}

bool TextWindow::handle_key_down(KeyPress keypress)
{
	std::string key = Chars::KEY_MAP[keypress.key_keyboard];

	if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("up")) scroll_up();
	else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("down")) scroll_down();
	else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("left")) scroll_left();
	else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("right")) scroll_right();
	else if (key == "RETURN") {
		add_text("...", false, false, false);
		on_return_key();
		_input = "";
		text.push_back("");
		return true;
	} else if (key == "DEL") {
		if (_input.size() > 0)
			_input.pop_back();
		remove_chars();
		return true;
	} else if (key == "unknown") return false;
	else {
		_input += key;
		add_text(key, false, false, false);
		return true;
	}
	return false;
}

Bitset2D TextWindow::update_window()
{
	if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time = Utils::us_since_boot();
		_show_cursor = !_show_cursor;
	}

	clear_window();
	create_menu();

	corner_y = current_page * 4 * line_height;

	return get_render_canvas();
}

void TextWindow::create_menu()
{
	for (uint32_t i = 0; i < text.size(); i++) {
		add_to_window(Graphics::create_text(text[i], Graphics::SYMBOLS_6_HIGH, text_spacing), 0, 1 + i * line_height);
	}
	if (_show_cursor) {
		if (text.size() == 0)
			add_to_window(Bitset2D(2, 9, true), 0, 0);
		else {
			uint16_t cursor_x = Utils::get_string_as_pixel_width(text.back(), Graphics::SYMBOLS_6_HIGH, text_spacing);
			uint16_t cursor_y = (text.size() - 1) * line_height;

			add_to_window(Bitset2D(2, 9, true), cursor_x, cursor_y);
		}
	}
}

int TextWindow::pages_count() const
{
	return static_cast<int>(ceil(static_cast<double>(text.size()) / 4));
}

void TextWindow::scroll_up()
{
	if (current_page > 0) current_page--;
}

void TextWindow::scroll_down()
{
	if (current_page < pages_count() - 1) current_page++;
}

void TextWindow::add_text(std::string text_to_add, bool keep_words, bool newline, bool leading_space)
{
	std::vector<std::string> words = Utils::split_string(text_to_add, ' ');

	if (newline || text.size() == 0)
		text.push_back("");

	if (leading_space)
		text[text.size() - 1] += " ";

	if (!keep_words) {
		for (int i = 0; i < text_to_add.size(); i++) {
			if (Utils::get_string_as_pixel_width(text[text.size() - 1] + text_to_add[i], Graphics::SYMBOLS_6_HIGH) > SCREEN_WIDTH)
				text.push_back("");

			if (text_to_add[i] == '\n')
				text.push_back("");
			else
				text[text.size() - 1] += text_to_add[i];
		}
	} else {
		for (int i = 0; i < words.size(); i++) {
			uint32_t word_width = Utils::get_string_as_pixel_width(words[i], Graphics::SYMBOLS_6_HIGH);

			if (Utils::get_string_as_pixel_width(text[text.size() - 1], Graphics::SYMBOLS_6_HIGH) + word_width > SCREEN_WIDTH)
				text.push_back("");

			if (word_width > SCREEN_WIDTH) {
				for (int j = 0; j < words[i].size(); j++) {
					if (Utils::get_string_as_pixel_width(text[text.size() - 1] + words[i][j], Graphics::SYMBOLS_6_HIGH) > SCREEN_WIDTH)
						text.push_back("");

					text[text.size() - 1] += words[i][j];
				}
				text[text.size() - 1] += " ";
			} else
				text[text.size() - 1] += words[i] + " ";
		}
	}

	current_page = pages_count() - 1;
}

void TextWindow::remove_chars()
{
	if (text.size() < 1) return;

	if (text[text.size() - 1].size() < 1)
		text.pop_back();

	if (text.size() < 1 || text[text.size() - 1].size() < 1) return;
	text[text.size() - 1].pop_back();
}

void TextWindow::on_return_key()
{
}