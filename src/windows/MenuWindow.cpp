#include "windows/MenuWindow.h"

MenuWindow::MenuWindow()
{
	this->window_manager = WindowManager::get_instance();
}

MenuWindow::~MenuWindow()
{
	for (size_t i = 0; i < options.size(); i++) { delete options[i]; }
	options.clear();
}

void MenuWindow::update_window()
{
	_frame.corner_y = current_page * 4 * line_height;
}

void MenuWindow::create_menu()
{
	for (size_t i = 0; i < options.size(); i++) {
		_window.put_chars(1, 1 + i * line_height, Graphics::SYMBOLS_6_HIGH, std::to_string(i) + ":" + options[i]->get_display_name(), true);
	}
}

int MenuWindow::pages_count() const
{
	return static_cast<int>(ceil(static_cast<double>(options.size()) / 4));
}

bool MenuWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == 167) scroll_up();
	else if (keypress.key_raw == 168) scroll_down();
	else if (keypress.key_raw == 169) {
		if (_frame.corner_x > 0) _frame.corner_x--;
	} else if (keypress.key_raw == 170) _frame.corner_x++;
	else if (keypress.key_raw < 10 && keypress.key_raw < options.size() && keypress.shift) options[keypress.key_raw]->on_shift_select();
	else if (keypress.key_raw < 10 && keypress.key_raw < options.size()) options[keypress.key_raw]->on_select();
	else return false;

	return true;
}

void MenuWindow::scroll_up()
{
	if (current_page > 0) current_page--;
}

void MenuWindow::scroll_down()
{
	if (current_page < pages_count() - 1) current_page++;
}