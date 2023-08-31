#include "MainMenu.h"
#include "Equation.h"
#include "Chars.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(const std::vector<MenuOption*>& options)
{
	this->_options = options;
}

bool MainMenu::delete_option(const std::string name)
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

void MainMenu::add_option(MenuOption* option, const int index)
{
	_options.insert(_options.begin() + index, option);
}

MenuOption* MainMenu::get_option(const std::string name)
{
	for (size_t i = 0; i < this->_options.size(); i++)
	{
		if (_options[i]->get_display_name() == name)
			return _options[i];
	}

	return nullptr;
}

const size_t MainMenu::options_size()
{
	return _options.size();
}

render_plane MainMenu::update_window()
{
	create_menu();

	corner_y = _current_page * 4 * _line_height;

	return get_render_canvas();
}

void MainMenu::create_menu()
{
	for (size_t i = 0; i < _options.size() && i < _max_options; i++)
	{
		add_to_window(Graphics::create_text(std::to_string(i) + ":" + _options[i]->get_display_name(), Graphics::SYMBOLS_6_HIGH, 1), 1, 1 + i * _line_height);
	}
}

const int MainMenu::pages_count()
{
	return static_cast<int>(ceil(static_cast<double>(_options.size()) / 4));
}

void MainMenu::handle_key_down(KeyPress keypress)
{
	std::cout << "Key pressed: " << +keypress.key_raw << std::endl;
	if (keypress.key_raw == Chars::KEY_MAP.at("up")) scroll_up();
	else if (keypress.key_raw == Chars::KEY_MAP.at("down")) scroll_down();
	else if (keypress.key_raw < 10) if (keypress.key_raw < _options.size()) _options[keypress.key_raw]->on_select();
}

void MainMenu::scroll_up()
{
	if(_current_page > 0)
		_current_page--;
}

void MainMenu::scroll_down()
{
	if(_current_page < pages_count() - 1)
		_current_page++;
}