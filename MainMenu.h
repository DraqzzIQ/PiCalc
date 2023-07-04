#pragma once

#include "IWindow.h"
#include "MenuOption.h"

#include <vector>

class MainMenu : public IWindow
{
	public:
		MainMenu();
		MainMenu(const std::vector<MenuOption>& options);

		int options_count(); 

		bool delete_option(const std::string name);
		void add_option(const MenuOption& option, const int index);
		MenuOption* get_option(const std::string name);

		void update(bool (&pixels)[SCREEN_HEIGHT][SCREEN_WIDTH]);


	private:
		std::vector<MenuOption> options;
};