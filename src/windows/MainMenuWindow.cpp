#include "windows/MainMenuWindow.h"

MainMenuWindow::MainMenuWindow():
	MenuWindow()
{
	options = std::vector<MenuOptionBase*>(9);
	options[0] = new MenuOption<CalculatorWindow>("Calculator");
	options[1] = new MenuOption<Window>("Notepad");
	options[2] = new MenuOption<SettingsWindow>("Settings");
	options[3] = new MenuOption<Window>("ChadGPT");
	options[4] = new MenuOption<Window>("DOOM");
	options[5] = new MenuOption<Window>("Another option with a really long name");
	options[6] = new MenuOption<Window>("Google");
	options[7] = new MenuOption<PaintWindow>("Paint");
	options[8] = new MenuOption<Window>("Option XyZ");

	create_menu();
}
