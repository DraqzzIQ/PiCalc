#include "windows/TextWindow.h"
#include "TextWindow.h"

TextWindow::TextWindow()
{
}

TextWindow::~TextWindow() {}

bool TextWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == 167) {
		scroll_up();
		return true;
	} else if (keypress.key_raw == 168) {
		scroll_down();
		return true;
	} else if (keypress.key_raw == 169) {
		if (_frame.corner_x > 0) _frame.corner_x--;
		return true;
	} else if (keypress.key_raw == 170) {
		_frame.corner_x++;
		return true;
	}
	return false;
}

void TextWindow::update_window()
{
	clear_window();
	create_menu();
	_frame.corner_y = _current_page * 4 * _line_height;
}

void TextWindow::create_menu()
{
	for (uint32_t i = 0; i < _text.size(); i++) {
		_window.put_chars(0, 1 + i * _line_height, Graphics::SYMBOLS_6_HIGH, _text[i], true);
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