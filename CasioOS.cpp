// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "ConsoleRenderer.h"
#include "WindowManager.h"
#include "MainMenu.h"
#include "Keyboard.h"
#include "Calculator.h"
#include <iostream>
#include <chrono>
#include <thread>

int fps = 30;
ConsoleRenderer* renderer;
WindowManager* window_manager;
Keyboard* keyboard;
MainMenu* main_menu;

/// <summary>
/// starts a thread that will update and render the window manager at set fps
/// </summary>
void start_render_thread()
{
	int frame_time = 1000 / fps;

	window_manager->update();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	window_manager->add_window(main_menu);

	while (1) {
		window_manager->update();
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
	options.push_back(new MenuOption("Calculator", window_manager));
	options.push_back(new MenuOption("Notepad", window_manager));
	options.push_back(new MenuOption("Settings", window_manager));
	options.push_back(new MenuOption("ChadGPT", window_manager));
	options.push_back(new MenuOption("DOOM", window_manager));
	options.push_back(new MenuOption("Another option with a really long name", window_manager));
	options.push_back(new MenuOption("Option x", window_manager));
	options.push_back(new MenuOption("Option X", window_manager));
	options.push_back(new MenuOption("Option XyZ", window_manager));

	options[0]->add_window<Calculator>();
	return options;
}

void start_kb_thread()
{
	keyboard = new Keyboard(window_manager);
}

/// <summary>
/// entry point
/// </summary>
int main(int argc, char* argv[])
{
	renderer = new ConsoleRenderer();
	window_manager = new WindowManager(renderer);
	main_menu = new MainMenu(create_main_menu_options());

	// start keyboard thread
	std::thread kb_thread(start_kb_thread);
	kb_thread.detach();

	// start render thread
	std::thread render_thread(start_render_thread);
	render_thread.join();

    return 0;
}