#include "MenuWindow.h"

MenuWindow::MenuWindow()
{
}

MenuWindow::MenuWindow(const std::vector<MenuOption*>& options)
{
	this->_options = options;
}

bool MenuWindow::delete_option(const std::string name)
{
	for (size_t i = 0; i < this->_options.size(); i++)
	{
		if (_options[i]->get_display_name() == name)
		{
			_options.erase(_options.begin() + i);
			return true;
		}
	}

	return false;
}

void MenuWindow::add_option(MenuOption* option, const int index)
{
	_options.insert(_options.begin() + index, option);
}

MenuOption* MenuWindow::get_option(const std::string name)
{
	for (size_t i = 0; i < this->_options.size(); i++)
	{
		if (_options[i]->get_display_name() == name)
			return _options[i];
	}

	return nullptr;
}

const size_t MenuWindow::options_size()
{
	return _options.size();
}

render_plane MenuWindow::update_window()
{
	create_menu();

	corner_y = _current_page * 4 * _line_height;

	return get_render_canvas();
}

void MenuWindow::create_menu()
{
	for (size_t i = 0; i < _options.size() && i < _max_options; i++)
	{
		add_to_window(Graphics::create_text(std::to_string(i) + ":" + _options[i]->get_display_name(), Graphics::SYMBOLS_6_HIGH, 1), 1, 1 + i * _line_height);
	}
}

const int MenuWindow::pages_count()
{
	return static_cast<int>(ceil(static_cast<double>(_options.size()) / 4));
}

void MenuWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == Chars::KEY_MAP.at("up")) scroll_up();
	else if (keypress.key_raw == Chars::KEY_MAP.at("down")) scroll_down();
    else if(keypress.key_raw == Chars::KEY_MAP.at("left")) scroll_left();
    else if(keypress.key_raw == Chars::KEY_MAP.at("right")) scroll_right();
	else if (keypress.key_raw < 10 && keypress.key_raw < _options.size()) _options[keypress.key_raw]->on_select();
}

void MenuWindow::scroll_up()
{
	if(_current_page > 0)
		_current_page--;
}

void MenuWindow::scroll_down()
{
	if(_current_page < pages_count() - 1)
		_current_page++;
}