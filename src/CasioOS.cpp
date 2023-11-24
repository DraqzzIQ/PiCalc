// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "renderers/ConsoleRenderer.h"
#include "keyboard/IKeyboard.h"
#include "renderers/IRenderer.h"
#include "windows/MainMenuWindow.h"
#include "utils/Utils.h"
#include "windows/WindowManager.h"
#include <iostream>
#include <vector>

#ifdef PICO
#include "renderers/DisplayRenderer.h"
#include "utils/I2CUtils.h"
#include "keyboard/PicoKeyboard.h"
#include "pico/stdlib.h"
#include <malloc.h>
#else
#include "keyboard/SDLKeyboard.h"
#include "http/DesktopHttpClient.h"
#endif

std::vector<IRenderer*>* renderers = new std::vector<IRenderer*>();
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
	std::cout << "Total Heap: " << Utils::get_total_heap() << std::endl;
	std::cout << "Free Heap: " << Utils::get_free_heap() << std::endl;
	I2CUtils::init_i2c();
	if (!I2CUtils::device_availible(DEVICE_ADDRESS)) std::cout << "Display not found" << std::endl;
	else renderers->push_back(new DisplayRenderer());
#else
	auto client = DesktopHttpClient("https://google.com");
	renderers->push_back(new ConsoleRenderer());
#endif
	window_manager = new WindowManager(renderers);
	window_manager->update();

	Utils::sleep_for_ms(1000);

	main_menu = new MainMenuWindow(window_manager);

#ifdef PICO
	keyboard = new PicoKeyboard(window_manager);
#else
	keyboard = new SDLKeyboard(window_manager);
	Utils::set_time_start_point();
#endif


	window_manager->add_window(main_menu);

	// start main thread
	start_main_thread();

	return 0;
}
