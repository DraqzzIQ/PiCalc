// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "keyboard/IKeyboard.h"
#include "renderers/ConsoleRenderer.h"
#include "renderers/IRenderer.h"
#include "utils/Utils.h"
#include "windows/MainMenuWindow.h"
#include "windows/WindowManager.h"
#include <iostream>
#include <vector>

#ifdef PICO
#include "keyboard/PicoKeyboard.h"
#include "pico/stdlib.h"
#include "renderers/DisplayRenderer.h"
#include "utils/I2CUtils.h"
#include <malloc.h>
#else
#include "keyboard/SDLKeyboard.h"
#endif


IKeyboard* keyboard;
WindowManager* window_manager;
MenuWindow* main_menu;

/// <summary>
/// starts a thread that will update and render the window manager
/// </summary>
void start_main_thread()
{
	while (1) {
		keyboard->check_for_keyboard_presses();
		window_manager->update(true);
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
	std::cout << "Total Heap: " << Utils::get_total_heap() << std::endl;
	std::cout << "Free Heap: " << Utils::get_free_heap() << std::endl;
	I2CUtils::init_i2c();
	// if (!I2CUtils::device_availible(LCD_DEVICE_ADDRESS)) std::cout << "Display not found" << std::endl;
	// else
	new DisplayRenderer();
#else
	new ConsoleRenderer();
#endif
	window_manager = WindowManager::get_instance();
	window_manager->update();

	Utils::sleep_for_ms(1000);

	main_menu = new MainMenuWindow();

#ifdef PICO
	keyboard = new PicoKeyboard();
#else
	keyboard = new SDLKeyboard();
	Utils::set_time_start_point();
#endif

	window_manager->add_window(main_menu);

	// start main thread
	start_main_thread();

	return 0;
}

// adding a new WIndow:
// 1. create a new class that inherits from Window
// 2. add a new MenuOption to MainMenuWindow.cpp and change size of options vector
// 3. add all needed virtual functions to the new class