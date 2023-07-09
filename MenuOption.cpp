#include "MenuOption.h"

MenuOption::MenuOption(const std::string display_name)
{
	_display_name = display_name;
}

void MenuOption::on_select()
{
	std::cout << "selected " << _display_name << std::endl;
}

std::string MenuOption::get_display_name()
{
	return _display_name;
}
