#include "windows/MenuWindow.h"

MenuWindow::MenuWindow(FONT& font, bool count):
	_font(font)
{
	_count = count;
	_line_height = _font.at(0).height() + 2;
	_lines_per_page = (SCREEN_HEIGHT + 2) / _line_height;
}

MenuWindow::MenuWindow(bool count):
	_font(Graphics::SYMBOLS_6_HIGH)
{
	_count = count;
	_line_height = _font.at(0).height() + 2;
	_lines_per_page = (SCREEN_HEIGHT + 2) / _line_height;
}

MenuWindow::~MenuWindow()
{
	for (MenuOptionBase* option : options) { delete option; }
	options.clear();
}

bool MenuWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == 167) scroll_up();
	else if (keypress.key_raw == 168) scroll_down();
	else if (keypress.key_raw == 169) {
		if (_frame.corner_x > 12) _frame.corner_x -= 13;
	} else if (keypress.key_raw == 170) _frame.corner_x += 13;
	else if (keypress.key_raw < 10 && keypress.key_raw < options.size() && keypress.shift) options[keypress.key_raw]->on_shift_select();
	else if (keypress.key_raw < 10 && keypress.key_raw < options.size()) options[keypress.key_raw]->on_select();
	else return false;

	return true;
}


void MenuWindow::create_menu()
{
	clear_window();
	for (uint8_t i = 0; i < _lines_per_page; i++) {
		uint8_t j = i + _page * _lines_per_page;
		if (j >= options.size()) break;
		_window.put_chars(0, 1 + i * _line_height, _font, (_count ? std::to_string(j) + ":" : "") + options[j]->display_name, true);
	}
}

void MenuWindow::scroll_up()
{
	if (_page > 0) _page--;
	create_menu();
}

void MenuWindow::scroll_down()
{
	if (options.size() != 0 && _page < (options.size() - 1) / _lines_per_page) _page++;
	create_menu();
}