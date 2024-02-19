// PiCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "keyboard/IKeyboard.h"
#include "renderers/ConsoleRenderer.h"
#include "threading/Threading.h"
#include "utils/Utils.h"
#include "windows/BatteryWindow.h"
#include "windows/MainMenuWindow.h"
#include "windows/WindowManager.h"
#include <iostream>
#include <vector>

#ifdef PICO
#include "http/PicoHttpClient.h"
#include "keyboard/PicoKeyboard.h"
#include "pico/stdlib.h"
#include "renderers/DisplayRenderer.h"
#include "utils/I2CUtils.h"
#include <malloc.h>
#else
#include "keyboard/SDLKeyboard.h"
#endif

IKeyboard* keyboard = nullptr;

/// <summary>
/// starts a thread that will update and render the window manager
/// </summary>
void start_main_thread()
{
#ifdef PICO
	multicore_launch_core1([]() {
		Threading::get_instance()->run();
	});
#else
	std::thread t([]() {
		Threading::get_instance()->run();
	});
	t.detach();
#endif
	uint64_t last_time = 0;
	uint8_t frame = 0;
	while (1) {
		keyboard->check_for_keyboard_presses();
		WindowManager::update();
		if (Utils::us_since_boot() - last_time < 1000000 / FPS) {
			Utils::sleep_for_us(1000000 / FPS - (Utils::us_since_boot() - last_time));
		}
		last_time = Utils::us_since_boot();
		frame++;
		if (frame == FPS) {
			frame = 0;
			Utils::update_voltage();
		}
	}
}

/// <summary>
/// entry point
/// </summary>
int main(int argc, char* argv[])
{
#ifdef PICO
	// GPIO 28 must be turned on for the pico to get power
	gpio_init(28);
	gpio_set_dir(28, GPIO_OUT);
	gpio_put(28, 1);

	// set up the battery voltage measuring pin (GPIO 26)
	// Not working yet
	adc_init();
	adc_gpio_init(26);
	adc_select_input(0);

	// set up the VBus voltage measurement pin (GPIO 24)
	// Not working yet
	gpio_init(24);
	gpio_set_dir(24, GPIO_IN);

	// Enable UART so status output can be printed
	stdio_init_all();
	std::cout << "Total Heap: " << Utils::get_total_heap() << std::endl;
	std::cout << "Free Heap: " << Utils::get_free_heap() << std::endl;
	I2CUtils::init_i2c();
	if (!I2CUtils::device_availible(LCD_DEVICE_ADDRESS)) std::cout << "Display not found" << std::endl;
	if (!I2CUtils::device_availible(POT_DEVICE_ADRESS)) std::cout << "Digital Potentiometer not found" << std::endl;
	keyboard = new PicoKeyboard();
#else
	Utils::set_time_start_point();
	keyboard = new SDLKeyboard();
#endif
	WindowManager::init(new MainMenuWindow());
	start_main_thread();

	return 0;
}

// adding a new Window:
// 1. create a new class that inherits from Window
// 2. add a new MenuOption to MainMenuWindow.cpp and change size of options vector
// 3. add all needed virtual functions to the new class