#pragma once

#include "Window.h"
#include "MenuOption.h"
#include "Constants.h"
#include "Graphics.h"

#include <vector>

class MainMenu : public Window
{
	public:
		MainMenu();
		MainMenu(const std::vector<MenuOption*>& options);

		int options_count(); 
		bool delete_option(const std::string name);
		void add_option(MenuOption* option, const int index);
		MenuOption* get_option(const std::string name);
		render_plane update_window();


	private:
		std::vector<MenuOption*> _options;
};