#pragma once
#include "options/WindowMenuOption.h"
#include "windows/ContrastWindow.h"
#include "windows/MenuWindow.h"
#include "windows/SysInfoWindow.h"

class SettingsWindow: public MenuWindow
{
	public:
	SettingsWindow():
		MenuWindow()
	{
		options = std::vector<MenuOptionBase*>(3);
		options[0] = new WindowMenuOption<SysInfoWindow>("System Info");
		options[1] = new WindowMenuOption<Window>("Wifi");
		options[2] = new WindowMenuOption<Window>("Secrets");
		options[2] = new WindowMenuOption<ContrastWindow>("Contrast");

		create_menu();
	}
};