#include "MainMenu.h"
#include "Equation.h"

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
	Equation e = Equation();
	e.addValue(L'1');
	e.addValue(L'2');
	e.addValue(L'3');
	e.addValue(FRACTION);
	e.addValue(L'4');
	e.addValue(L'2');
	e.moveCursor('r');
	e.addValue(L'4');
	e.moveCursor('r');
	e.addValue(L'7');
	e.moveCursor('r');
	e.addValue('A');
	e.moveCursor('r');
	e.moveCursor('r');
	e.moveCursor('r');
	e.moveCursor('r');
	add_to_window(Graphics::create_text(std::format(L"ABC{}", PI), Graphics::SYMBOLS_6_HIGH), 10, 10);
	return get_render_canvas();
}