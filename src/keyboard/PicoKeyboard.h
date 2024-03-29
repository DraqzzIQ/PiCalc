#pragma once
#ifdef PICO
#include "keyboard/IKeyboard.h"
#include "windows/WindowManager.h"
#include <iostream>
#include <map>
#include <pico/stdlib.h>
#include <vector>

/// <summary>
///  gets keyboard input from pico
/// </summary>
class PicoKeyboard: public IKeyboard
{
	public:
	/// <summary>
	/// constructs a new keyboard-listener
	/// </summary>
	PicoKeyboard();
	/// <summary>
	/// checks for keyboard presses
	/// </summary>
	void check_for_keyboard_presses() override;

	protected:
	/// <summary>
	/// checks wether shift is active
	/// </summary>
	/// <returns>true if pressed else false</returns>
	bool is_shift_active() override;
	/// <summary>
	/// checks wether alpha is active
	/// </summary>
	/// <returns>true if pressed else false</returns>
	bool is_alpha_active() override;

	private:
	/// <summary>
	/// provides the states used for the function key tracking (shift + alpha)
	/// is also used to save with which function key activated a button was pressed to later output the correct key using that info
	/// (otherwise if you press a key with shift, on the release of that key another keycode will be returned)
	/// </summary>
	enum class KeyState { OFF,
		                  ON,
		                  SHIFT_ON,
		                  ALPHA_ON };
	/// <summary>
	/// keeps track which function key (shift / alpha) is activated using the KeyState enumerator
	/// </summary>
	KeyState _function_keys_state = KeyState::ON;
	/// <summary>
	/// the GPIO numbers to be used as input for the button matrix
	/// </summary>
	const std::vector<uint8_t> _inputs{ 2, 3, 6, 7, 8, 9, 10, 11, 12 };
	/// <summary>
	/// the GPIO numbers to be used as output for the button matrix
	/// </summary>
	const std::vector<uint8_t> _outputs{ 13, 14, 15, 20, 21, 22 };
	/// <summary>
	/// Saves, which key is currently pressed and how it was pressed (shift / alpha / none) using the KeyState enumerator
	/// </summary>
	std::vector<std::vector<KeyState>> _pressed_buttons = std::vector<std::vector<KeyState>>(_outputs.size(), std::vector<KeyState>(_inputs.size(), KeyState::OFF));
	/// <summary>
	/// sets all pins in the outputs vector to low except the one selected, used for the button matrix
	/// </summary>
	/// <param name="pin">pin to pull high</param>
	void set_pin(uint8_t pin);
	/// <summary>
	/// reads all pins from the input vector and returns the result, used for the button matrix
	/// </summary>
	/// <returns>values (LOW = false, HIGH = true) of the nine input pins</returns>
	std::vector<bool> get_pins();
	/// <summary>
	/// converts the coordinates of a key action to an instance of the KeyPress class to be passed to other classes
	/// </summary>
	/// <param name="x">x coordinate (0-5) of the key action</param>
	/// <param name="y">y coordinate (0-8) of the key action</param>
	/// <param name="state">function key that should be used for converting</param>
	/// <returns>instance of KeyPress class</returns>
	KeyPress coords_to_keypress(uint8_t x, uint8_t y, KeyState state);
	/// <summary>
	/// converts the coordinates of a key action to its corresponding keycode ignoring function keys
	/// </summary>
	/// <param name="x">x coordinate (0-5) of the key action</param>
	/// <param name="y">y coordinate (0-8) of the key action</param>
	/// <returns>keycode</returns>
	KEY coords_to_key_raw(uint8_t x, uint8_t y);
	/// <summary>
	/// converts raw keycodes to calculator keycodes using the normal keyboard key-layout
	/// </summary>
	KEY raw_key_to_keyboard_key(KEY raw_key, bool shift, bool alpha);
};
#endif
