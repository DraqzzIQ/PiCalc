#include "windows/MenuWindow.h"

MenuWindow::MenuWindow(FONT& font, CountType count):
	_font(font)
{
	_count_type = count;
	_line_height = _font.at(0).height() + 2;
	_lines_per_page = (SCREEN_HEIGHT + 2) / _line_height;
}

MenuWindow::MenuWindow(CountType count):
	_font(Graphics::SYMBOLS_6_HIGH)
{
	_count_type = count;
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
	if (keypress.key_raw == KEY_UP) scroll_up();
	else if (keypress.key_raw == KEY_DOWN) scroll_down();
	else if (keypress.key_raw == KEY_LEFT) {
		if (_frame.corner_x > 12) _frame.corner_x -= 13;
	} else if (keypress.key_raw == KEY_RIGHT) _frame.corner_x += 13;
	else if (_count_type == CountType::CUSTOM) {
		for (MenuOptionBase* option : options) {
			if (keypress.key_raw == option->select_key) {
				if (keypress.shift) option->on_shift_select();
				else option->on_select();
				return true;
			}
		}
		return false;
	} else if (_count_type == CountType::CONTINUOUS && (keypress.key_raw -= 48) < options.size()) {
		if (keypress.shift) options[keypress.key_raw]->on_shift_select();
		else options[keypress.key_raw]->on_select();
	} else if (_count_type == CountType::REPEATING && (keypress.key_raw -= 48) < _lines_per_page) {
		uint8_t j = keypress.key_raw + _page * _lines_per_page;
		if (j < options.size()) {
			if (keypress.shift) options[j]->on_shift_select();
			else options[j]->on_select();
			return true;
		}
		return false;
	} else return false;

	return true;
}


void MenuWindow::create_menu()
{
	clear_window();
	if (options.size() > 9) _count_type = CountType::REPEATING;
	for (uint8_t i = 0; i < _lines_per_page; i++) {
		uint8_t j = i + _page * _lines_per_page;
		if (j >= options.size()) break;
		std::string name = options[j]->display_name;
		if (_count_type == CountType::REPEATING) name = std::to_string(j % _lines_per_page) + ":" + name;
		else if (_count_type == CountType::CONTINUOUS) name = std::to_string(j) + ":" + name;
		_window.put_chars(0, 1 + i * _line_height, _font, name, true);
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