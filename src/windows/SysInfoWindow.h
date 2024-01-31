#pragma once
#include "options/TextMenuOption.h"
#include "utils/Utils.h"
#include "windows/MenuWindow.h"

class SysInfoWindow: public MenuWindow
{
	public:
	SysInfoWindow():
		MenuWindow(false)
	{
		options = std::vector<MenuOptionBase*>(3);
		options[0] = new TextMenuOption("OS Version: " + OS_VERSION);
		options[1] = new TextMenuOption("Total Heap: " + std::to_string(Utils::get_total_heap()));
		options[2] = new TextMenuOption("Free Heap: " + std::to_string(Utils::get_free_heap()));

		_frame.screen_symbols = 0xFFFF;
		create_menu();
	}

	void update_window() override
	{
		options[1] = new TextMenuOption("Total Heap: " + std::to_string(Utils::get_total_heap()));
		options[2] = new TextMenuOption("Free Heap: " + std::to_string(Utils::get_free_heap()));
		create_menu();
	}
};
