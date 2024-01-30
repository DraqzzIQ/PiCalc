#pragma once
#include "options/WindowMenuOption.h"
#include "windows/BatteryWindow.h"
#include "windows/ContrastWindow.h"
#include "windows/MenuWindow.h"
#include "windows/SysInfoWindow.h"

class SettingsWindow: public MenuWindow
{
	public:
	SettingsWindow()
	{
		options = std::vector<MenuOptionBase*>(5);
		options[0] = new WindowMenuOption<SysInfoWindow>("System Info");
		options[1] = new WindowMenuOption<Window>("Wifi");
		options[2] = new WindowMenuOption<Window>("Secrets");
		options[3] = new WindowMenuOption<ContrastWindow>("Contrast");
		options[4] = new WindowMenuOption<BatteryWindow>("Battery");

		create_menu();
	}
};