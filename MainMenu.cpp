#include "MainMenu.h"

#include <vector>

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(const std::vector<MenuOption>& options)
{
	this->_options = options;
}

int MainMenu::options_count()
{
	return this->_options.size();
}

bool MainMenu::delete_option(const std::string name)
{
	for (int i = 0; i < this->_options.size(); i++)
	{
		if (_options[i].display_name == name)
		{
			_options.erase(_options.begin() + i);
			return true;
		}
	}

	return false;
}

void MainMenu::add_option(const MenuOption& option, const int index)
{
	_options.insert(_options.begin() + index, option);
}

MenuOption* MainMenu::get_option(const std::string name)
{
	for (int i = 0; i < this->_options.size(); i++)
	{
		if (_options[i].display_name == name)
			return &_options[i];
	}

	return nullptr;
}

void update(bool(&pixels)[SCREEN_HEIGHT][SCREEN_WIDTH])
{

}