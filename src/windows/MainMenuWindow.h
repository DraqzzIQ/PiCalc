#pragma once
#include "windows/CalculatorWindow.h"
#include "windows/ChatGPTWindow.h"
#include "windows/MenuWindow.h"
#include "windows/NotesWindow.h"
#include "windows/PaintWindow.h"
#include "windows/PongWindow.h"
#include "windows/SettingsWindow.h"
#include "windows/WolframAlphaWindow.h"

class MainMenuWindow: public MenuWindow
{
	public:
	MainMenuWindow()
	{
		options = std::vector<MenuOptionBase*>(7);
		options[0] = new WindowMenuOption<CalculatorWindow>("Calculator");
		// temporarily disabled
		options[1] = new WindowMenuOption<Window>("Wolfram Alpha");
		options[2] = new WindowMenuOption<Window>("ChadGPT");
		options[3] = new WindowMenuOption<Window>("Notes");
		options[4] = new WindowMenuOption<PongWindow>("Pong");
		options[5] = new WindowMenuOption<PaintWindow>("Paint");
		options[6] = new WindowMenuOption<SettingsWindow>("Settings");

		create_menu();
	}
};