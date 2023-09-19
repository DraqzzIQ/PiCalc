// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "IRenderer.h"
#include "ConsoleRenderer.h"
#include "WindowManager.h"
#include "MainMenuWindow.h"
#include "IKeyboard.h"
#include "Utils.h"
#include <iostream>
#include <vector>

#ifdef PICO
#include "PicoKeyboard.h"
#include "DisplayRenderer.h"
#include "pico/stdlib.h"
#include "I2CUtils.h"
#include "BTManager.h"
#include "BTRenderer.h"
#include <malloc.h>
#else
#include "SDLKeyboard.h"
#endif

std::vector<IRenderer*>* renderers = new std::vector<IRenderer*>();
IKeyboard* keyboard;
WindowManager* window_manager;
MenuWindow* main_menu;
#ifdef PICO
BTManager* bt_manager;
#endif

/// <summary>
/// starts a thread that will update and render the window manager
/// </summary>
void start_main_thread()
{
	while (1) {
		keyboard->check_for_keyboard_presses();
		window_manager->update();
		std::cout << Utils::us_since_boot() << "us" << std::endl;
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
	if(!I2CUtils::device_availible(DEVICE_ADDRESS))
		std::cout << "Display not found" << std::endl;
	else
		renderers->push_back(new DisplayRenderer());
	renderers->push_back(new BTRenderer(bt_manager));
#else
	renderers->push_back(new ConsoleRenderer());
#endif
	window_manager = new WindowManager(renderers);
	window_manager->update();
	
	Utils::sleep_for_ms(1000);

	main_menu = new MainMenuWindow(window_manager);

#ifdef PICO
	keyboard = new PicoKeyboard(window_manager);
	bt_manager = new BTManager(window_manager);
	bt_manager->enable_bt();
#else
	keyboard = new SDLKeyboard(window_manager);
	Utils::set_start_point();
#endif

	window_manager->add_window(main_menu);

	// start main thread
	start_main_thread();

    return 0;
}