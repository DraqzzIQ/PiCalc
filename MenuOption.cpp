#include "MenuOption.h"
#include "Calculator.h"
#include "WindowManager.h"

MenuOption::MenuOption(const std::string display_name, WindowManager* window_manager){
	_display_name = display_name;
	_window_manager = window_manager;
}

void MenuOption::on_select()
{
	std::cout << "selected " << _display_name << std::endl;
	if (_window_name != nullptr) {
		_window_manager->add_window(_window_name);
	}
}

std::string MenuOption::get_display_name()
{
	return _display_name;
}
