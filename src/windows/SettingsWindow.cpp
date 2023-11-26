#include "windows/SettingsWindow.h"

SettingsWindow::SettingsWindow():
	MenuWindow()
{
	options = std::vector<MenuOptionBase*>(3);
	options[0] = new MenuOption<SysInfoWindow>("System Info");
	options[1] = new MenuOption<Window>("Wifi");
	options[2] = new MenuOption<Window>("Secrets");

	create_menu();
}
