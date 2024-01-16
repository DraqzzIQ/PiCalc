#include "windows/MainMenuWindow.h"

MainMenuWindow::MainMenuWindow():
	MenuWindow()
{
	options = std::vector<MenuOptionBase*>(10);
	options[0] = new MenuOption<CalculatorWindow>("Calculator");
	options[1] = new MenuOption<WolframAlphaWindow>("Wolfram Alpha");
	options[2] = new MenuOption<SettingsWindow>("Settings");
	options[3] = new MenuOption<ChatGPTWindow>("ChadGPT");
	options[4] = new MenuOption<Window>("Notepad");
	options[5] = new MenuOption<Window>("DOOM");
	options[6] = new MenuOption<PongWindow>("Pong");
	options[7] = new MenuOption<Window>("Google");
	options[8] = new MenuOption<PaintWindow>("Paint");
	options[9] = new MenuOption<Window>("Option XyZ");

	create_menu();
}
