// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "IRenderer.h"
#include "WindowManager.h"
#include "MainMenu.h"
#include "IKeyboard.h"
#include "Calculator.h"
#include "Utils.h"
#include <iostream>

#ifdef PICO
#include "PicoKeyboard.h"
#include "DisplayRenderer.h"
#include "pico/stdlib.h"
#else
#include "SDLKeyboard.h"
#include "ConsoleRenderer.h"
#endif

IRenderer* renderer;
IKeyboard* keyboard;
WindowManager* window_manager;
MainMenu* main_menu;


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

/// <summary>
/// starts a thread that will update and render the window manager at set fps
/// </summary>
void start_main_thread()
{
	while (1) {
		keyboard->check_for_keyboard_presses();
		window_manager->update();
	}
}

/// <summary>
/// entry point
/// </summary>
int main(int argc, char* argv[])
{
#ifdef PICO
	// Enable UART so we can print status output
    stdio_init_all();
	renderer = new DisplayRenderer();
#else
	renderer = new ConsoleRenderer();
#endif
	window_manager = new WindowManager(renderer);
	window_manager->update();
	
	Utils::sleep_for_ms(1000);

	main_menu = new MainMenu(create_main_menu_options());
	window_manager->update();

#ifdef PICO
	keyboard = new PicoKeyboard(window_manager);
#else
	keyboard = new SDLKeyboard(window_manager);
#endif

	window_manager->add_window(main_menu);

	// start main thread
	start_main_thread();

    return 0;
}