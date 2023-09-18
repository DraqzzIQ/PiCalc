#include "MainMenuWindow.h"

MainMenuWindow::MainMenuWindow(WindowManager *window_manager) : MenuWindow(window_manager)
{
    options = std::vector<MenuOption*>(9);
    options[0] = new CalculatorOption(window_manager);
	options[1] = new MenuOption("Notepad ", window_manager);
	options[2] = new SettingsOption(window_manager);
	options[3] = new MenuOption("ChadGPT", window_manager);
	options[4] = new MenuOption("DOOM", window_manager);
	options[5] = new MenuOption("Another option with a really long name", window_manager);
	options[6] = new MenuOption("Option x", window_manager);
	options[7] = new MenuOption("Option X", window_manager);
	options[8] = new MenuOption("Option XyZ", window_manager);
}