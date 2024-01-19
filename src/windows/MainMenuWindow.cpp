#include "windows/MainMenuWindow.h"

MainMenuWindow::MainMenuWindow():
	MenuWindow()
{
	options = std::vector<MenuOptionBase*>(7);
	options[0] = new WindowMenuOption<CalculatorWindow>("Calculator");
	options[1] = new WindowMenuOption<WolframAlphaWindow>("Wolfram Alpha");
	options[2] = new WindowMenuOption<ChatGPTWindow>("ChadGPT");
	options[3] = new WindowMenuOption<NotesWindow>("Notes");
	options[4] = new WindowMenuOption<PongWindow>("Pong");
	options[5] = new WindowMenuOption<PaintWindow>("Paint");
	options[6] = new WindowMenuOption<SettingsWindow>("Settings");

	create_menu();
}
