#include "windows/TextWindow.h"
#include "TextWindow.h"

TextWindow::~TextWindow() {}

bool TextWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("up")) {
		scroll_up();
		return true;
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("down")) {
		scroll_down();
		return true;
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("left")) {
		scroll_left();
		return true;
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("right")) {
		scroll_right();
		return true;
	}
	return false;
}

Frame TextWindow::update_window()
{
	clear_window();
	create_menu();

	_corner_y = _current_page * 4 * _line_height;

	return Frame(get_render_canvas(), _screen_symbols);
}

void TextWindow::create_menu()
{
	for (uint32_t i = 0; i < _text.size(); i++) {
		add_to_window(Graphics::create_text(_text[i], Graphics::SYMBOLS_6_HIGH, _text_spacing), 0, 1 + i * _line_height);
	}
}

int TextWindow::pages_count() const
{
	return static_cast<int>(ceil(static_cast<double>(_text.size()) / 4));
}

void TextWindow::scroll_up()
{
	if (_current_page > 0) _current_page--;
}

void TextWindow::scroll_down()
{
	if (_current_page < pages_count() - 1) _current_page++;
}