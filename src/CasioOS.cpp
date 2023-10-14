// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "ConsoleRenderer.h"
#include "IKeyboard.h"
#include "IRenderer.h"
#include "MainMenuWindow.h"
#include "Utils.h"
#include "WindowManager.h"
#include <iostream>
#include <vector>

#ifdef PICO
#include "BTManager.h"
#include "BTOut.h"
#include "BTRenderer.h"
#include "DisplayRenderer.h"
#include "I2CUtils.h"
#include "PicoKeyboard.h"
#include "StreamBufferCapturer.h"
#include "pico/stdlib.h"
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
BTOut* bt_out;
StreamBufferCapturer* cout_capturer;
StreamBufferCapturer* cerr_capturer;
#endif

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
	renderers->push_back(new BTRenderer(bt_manager));

	bt_out = new BTOut(bt_manager);
	cout_capturer = new StreamBufferCapturer(std::cout.rdbuf(), bt_out);
	cerr_capturer = new StreamBufferCapturer(std::cerr.rdbuf(), bt_out);
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
	std::cout.rdbuf(cout_capturer);
	std::cerr.rdbuf(cerr_capturer);
#else
	keyboard = new SDLKeyboard(window_manager);
	Utils::set_time_start_point();
#endif


	window_manager->add_window(main_menu);

	// start main thread
	start_main_thread();

	return 0;
}