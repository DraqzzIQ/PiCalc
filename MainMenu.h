#pragma once

#include "IRenderItem.h"
#include "MenuOption.h"

#include <vector>

class MainMenu : public IRenderItem
{
	public:
		MainMenu();
		MainMenu(const std::vector<MenuOption>& options);

		int options_count(); 

		bool delete_option(const std::string name);
		void add_option(const MenuOption& option, const int index);
		MenuOption* get_option(const std::string name);
		
		void update(bool (&pixels)[32][96]);

	private:
		std::vector<MenuOption> options;
};