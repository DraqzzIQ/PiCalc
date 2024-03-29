#pragma once
#include "constant/Chars.h"
#include "windows/WindowManager.h"

/// <summary>
/// provides an interface for keyboard input
/// </summary>
class IKeyboard
{
	public:
	/// <summary>
	/// checks for keyboard presses
	/// </summary>
	virtual void check_for_keyboard_presses() = 0;

	protected:
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
	static KEY raw_key_to_calculator_key(KEY raw_key, bool shift, bool alpha);
	/// <summary>
	/// window manager handles the inputs
	/// </summary>
	WindowManager* _window_manager;
};
