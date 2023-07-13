#pragma once
#include "WindowManager.h"
#include "SDL.h"
#include <chrono>
#include <thread>
#include <iostream>

/// <summary>
///  gets keyboard input on different platforms
/// </summary>
class Keyboard
{
	public:
		Keyboard(WindowManager* window_manager);

		/// <summary>
		/// converts a scancode to a number, returns -1 if scancode is no number
		/// </summary>
		/// <param name="scancode">scancode to check</param>
		/// <returns>true if number</returns>
		static int scancode_to_number(int scancode);
	private:
		/// <summary>
		/// window manager handles the inputs
		/// </summary>
		WindowManager* _window_manager;
		/// <summary>
		/// sdl window used to get keyboard input
		/// </summary>
		SDL_Window* window;
		/// <summary>
		/// initializes sdl
		/// </summary>
		void sdl_init();
		/// <summary>
		/// checks for keyboard events
		/// </summary>
		void check_for_keyboard_events();
		/// <summary>
		/// checks for calc button presses
		/// </summary>
		void check_for_calc_button_presses();
		/// <summary>
		/// avoid unnecessary cpu usage
		/// </summary>
		int _sleep_time = 10;
};

