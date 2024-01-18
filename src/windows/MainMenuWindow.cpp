#include "windows/MainMenuWindow.h"

MainMenuWindow::MainMenuWindow():
	MenuWindow()
{
	options = std::vector<MenuOptionBase*>(7);
	options[0] = new WindowMenuOption<CalculatorWindow>("Calculator");
	options[1] = new WindowMenuOption<WolframAlphaWindow>("Wolfram Alpha");
	options[2] = new WindowMenuOption<SettingsWindow>("Settings");
	options[3] = new WindowMenuOption<ChatGPTWindow>("ChadGPT");
	options[4] = new WindowMenuOption<Window>("Notepad");
	options[5] = new WindowMenuOption<PongWindow>("Pong");
	options[6] = new WindowMenuOption<PaintWindow>("Paint");

	create_menu();
}
