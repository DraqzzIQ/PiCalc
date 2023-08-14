#pragma once
#ifdef PICO
#include "WindowManager.h"
#include "IKeyboard.h"
#include <iostream>
#include <vector>
#include <pico/stdlib.h>

/// <summary>
///  gets keyboard input from pico
/// </summary>
class PicoKeyboard : public IKeyboard
{
	public:
		/// <summary>
		/// constructs a new keyboard-listener
		/// </summary>
		/// <param name="window_manager">windowmanager do send keyevents to</param>
		PicoKeyboard(WindowManager* window_manager);
		/// <summary>
		/// checks for keyboard presses
		/// </summary>
		void check_for_keyboard_presses();
		/// <summary>
		/// checks wether shift is active
		/// </summary>
		/// <returns>true if pressed else false</returns>
		bool is_shift_active();
		/// <summary>
		/// checks wether alpha is active
		/// </summary>
		/// <returns>true if pressed else false</returns>
		bool is_alpha_active();
	private:
        bool is_shift = false;
        bool is_alpha = false;

		const std::vector<uint8_t> inputs{2, 3, 6, 7, 8, 9, 10, 11, 12};
		const std::vector<uint8_t> outputs{13, 14, 15, 16, 17, 18};
		std::vector<std::vector<bool>> pressedButtons = std::vector<std::vector<bool>>(outputs.size(), std::vector<bool>(inputs.size(), 0));

		void setPin(uint8_t pin);
		std::vector<bool> getPins();

		KeyPress coords_to_keypress(uint8_t x, uint8_t y);
		uint8_t coords_to_keycode(uint8_t x, uint8_t y, bool raw = false);
};
#endif