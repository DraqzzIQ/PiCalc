#pragma once
#ifdef PICO
#include "WindowManager.h"
#include "IKeyboard.h"
#include <iostream>

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
};
#endif