#include "MainMenu.h"

#include <vector>

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(const std::vector < MenuOption > & options)
{
	this->options = options;
}

int MainMenu::options_count()
{
	return this->options.size();
}

bool MainMenu::delete_option(const std::string name)
{
	for (int i = 0; i < this->options.size(); i++)
	{
		if (options[i].display_name == name)
		{
			options.erase(options.begin() + i);
			return true;
		}
	}

	return false;
}

void MainMenu::add_option(const MenuOption& option, const int index)
{
	options.insert(options.begin() + index, option);
}

MenuOption* MainMenu::get_option(const std::string name)
{
	for (int i = 0; i < this->options.size(); i++)
	{
		if (options[i].display_name == name)
			return &options[i];
	}

	return nullptr;
}

void MainMenu::update()
{

}