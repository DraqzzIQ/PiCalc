#include "windows/SettingsWindow.h"

SettingsWindow::SettingsWindow():
	MenuWindow()
{
	options = std::vector<MenuOptionBase*>(3);
	options[0] = new WindowMenuOption<SysInfoWindow>("System Info");
	options[1] = new WindowMenuOption<Window>("Wifi");
	options[2] = new WindowMenuOption<Window>("Secrets");

	create_menu();
}
