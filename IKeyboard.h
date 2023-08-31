#pragma once
#include "WindowManager.h"

/// <summary>
/// provides an interface for keyboard input
/// </summary>
class IKeyboard
{
	public:
        IKeyboard(WindowManager* window_manager);
		virtual ~IKeyboard() {};
		/// <summary>
		/// checks for keyboard presses
		/// </summary>
		virtual void check_for_keyboard_presses() = 0;
		/// <summary>
		/// checks wether shift is active
		/// </summary>
		/// <returns>true if active else false</returns>
		virtual bool is_shift_active() = 0;
		/// <summary>
		/// checks wether alpha is active
		/// </summary>
		/// <returns>true if active else false</returns>
		virtual bool is_alpha_active() = 0;
		/// <summary>
		/// converts raw keycodes to calculator keycodes using the calculator key-layout
		/// </summary>
		static uint8_t raw_key_to_calculator_key(uint8_t raw_key, bool shift, bool alpha);
		/// <summary>
		/// converts raw keycodes to calculator keycodes using the normal keyboard key-layout
		/// </summary>
		static uint8_t raw_key_to_keyboard_key(uint8_t raw_key, bool shift, bool alpha);
        /// <summary>
		/// window manager handles the inputs
		/// </summary>
		WindowManager* _window_manager;
    private:
};