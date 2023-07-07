#include "MainMenu.h"

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

render_plane MainMenu::update_window()
{
	return Graphics::EMPTY_SCREEN;
}