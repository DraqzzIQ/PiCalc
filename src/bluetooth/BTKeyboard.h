#pragma once
#ifdef PICO
#include "keyboard/IKeyboard.h"
#include "keyboard/KeyPress.h"

class BTKeyboard: public IKeyboard
{
	public:
	BTKeyboard(WindowManager* window_manager);
	/// <summary>
	/// creates a KeyPress struct out of an BT keycode
	/// </summary>
	/// <param name="key">bt_keycode</param>
	/// <returns>KeyPress</returns>
	KeyPress get_key_press(uint8_t keycode);
	/// <summary>
	/// checks wether shift is active
	/// </summary>
	bool is_shift_active();
	/// <summary>
	/// checks wether alpha is active
	/// </summary>
	bool is_alpha_active();
	/// <summary>
	/// unused
	/// </summary>
	void check_for_keyboard_presses();
	/// <summary>
	/// handle keyboard press
	/// </summary>
	void handle_keyboard_press(uint8_t bt_keycode);

	private:
	/// <summary>
	/// converts BT keycodes to calculator keycodes using the calculator key-layout, but ignores shift + alpha
	/// </summary>
	/// <param name="key">bt_keycode</param>
	/// <returns>keycode</returns>
	uint8_t bt_keycode_to_raw_key(uint8_t bt_keycode);
	/// <summary>
	/// enum for the state of the function keys
	/// </summary>
	enum FunctionKeyState { OFF, SHIFT_ON, ALPHA_ON };
	/// <summary>
	/// state of the function keys
	/// </summary>
	FunctionKeyState functionKeysState = FunctionKeyState::OFF;
};
#endif
