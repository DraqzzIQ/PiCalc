#include "options/MenuOption.h"

MenuOption::MenuOption(const std::string display_name, WindowManager* window_manager)
{
	this->display_name = display_name;
	this->window_manager = window_manager;
}

void MenuOption::on_select() {}

void MenuOption::on_shift_select() {}

std::string MenuOption::get_display_name()
{
	return display_name;
}
