// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "ConsoleRenderer.h"
#include "WindowManager.h"
#include "MainMenu.h"
#include "Keyboard.h"
#include <iostream>
#include <chrono>
#include <thread>

int fps = 30;
ConsoleRenderer* renderer;
WindowManager* windowManager;
Keyboard* keyboard;
MainMenu* mainMenu;

/// <summary>
/// starts a thread that will update and render the window manager at set fps
/// </summary>
void start_render_thread()
{
	int frame_time = 1000 / fps;

	while (1) {
		windowManager->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(frame_time));
	}
}
/// <summary>
/// creates the main menu options
/// </summary>
/// <returns>menu options</returns>
std::vector<MenuOption*> create_main_menu_options()
{
	std::vector<MenuOption*> options;
	options.push_back(new MenuOption("Calculator"));
	options.push_back(new MenuOption("Notepad"));
	options.push_back(new MenuOption("Settings"));
	options.push_back(new MenuOption("ChadGPT"));
	options.push_back(new MenuOption("DOOM"));
	options.push_back(new MenuOption("Another option with a really long name"));
	options.push_back(new MenuOption("Option x"));
	options.push_back(new MenuOption("Option X"));
	options.push_back(new MenuOption("Option XyZ"));


	return options;
}

void start_kb_thread()
{
	keyboard = new Keyboard(windowManager);
}

/// <summary>
/// entry point
/// </summary>
int main(int argc, char* argv[])
{
	renderer = new ConsoleRenderer();
	windowManager = new WindowManager(renderer);
	mainMenu = new MainMenu(create_main_menu_options());

	windowManager->add_window(mainMenu);
	windowManager->update();

	// start keyboard thread
	std::thread kb_thread(start_kb_thread);
	kb_thread.detach();

	// start render thread
	std::thread render_thread(start_render_thread);
	render_thread.join();

    return 0;
}