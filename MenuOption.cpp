#include "MenuOption.h"

MenuOption::MenuOption(const std::string display_name)
{
	this->display_name = display_name;
}

std::string MenuOption::get_display_name()
{
	return display_name;
}
