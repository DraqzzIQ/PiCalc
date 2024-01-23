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
	/// returns instance of singleton PicoKeyboard
	/// </summary>
	static PicoKeyboard* get_instance();

	protected:
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
	/// <summary>
	/// private constructor to prevent instantiation
	/// </summary>
	PicoKeyboard();
	/// <summary>
	/// private deconstructor to prevent deletion
	/// </summary>
	~PicoKeyboard();
	/// <summary>
	/// private copy constructor and assignmnt operator to prevent copying
	/// </summary>
	PicoKeyboard(const PicoKeyboard&);
	PicoKeyboard& operator=(const PicoKeyboard&);
	/// <summary>
	/// the instance
	/// </summary>
	static PicoKeyboard* _instance;
	/// <summary>
	/// provides the states used for the function key tracking (shift + alpha)
	/// is also used to save with which function key activated a button was pressed to later output the correct key using that info
	/// (otherwise if you press a key with shift, on the release of that key another keycode will be returned)
	/// </summary>
	enum class KeyState { OFF,
		                  ON,
		                  SHIFT_ON,
		                  ALPHA_ON };

	static void interrupt_callback(uint gpio, uint32_t events);
	/// <summary>
	/// handles the button press interrupts
	/// </summary>
	void button_pressed(uint gpio, uint32_t events);
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
	/// sets all pins in the outputs vector to value
	/// </summary>
	/// <param name="value">HIGH or LOW</param>
	void set_pins(bool value);
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
	/// prints the name of the key being input, used for debugging
	/// </summary>
	/// <param name="key">keycode of the key being printed</param>
	void print_key(KEY key);
};
#endif
