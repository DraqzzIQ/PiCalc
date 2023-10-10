#pragma once
#ifndef PICO
#include "Chars.h"
#include "IKeyboard.h"
#include <SDL2/SDL.h>
#include "WindowManager.h"
#include <iostream>

/// <summary>
///  gets keyboard input from SDL
/// </summary>
class SDLKeyboard: public IKeyboard
{
	public:
	/// <summary>
	/// constructs a new keyboard-listener
	/// </summary>
	/// <param name="window_manager">windowmanager do send keyevents to</param>
	SDLKeyboard(WindowManager* window_manager);
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
	/// <summary>
	/// SDL window used to get keyboard input
	/// </summary>
	SDL_Window* _window;
	/// <summary>
	/// SDL event
	/// </summary>
	SDL_Event* _event;
	/// <summary>
	/// initializes SDL
	/// </summary>
	void sdl_init();
	/// <summary>
	/// creates a KeyPress struct out of an SDL event
	/// </summary>
	KeyPress sdl_event_to_keypress(SDL_Event* _event);
	/// <summary>
	/// converts SDL scancodes to calculator keycodes using the normal keyboard key-layout
	/// </summary>
	/// <param name="key">scancode</param>
	/// <returns>keycode</returns>
	uint8_t scancode_to_key_keyboard(SDL_Event* _event);
	/// <summary>
	/// converts SDL scancodes to calculator keycodes using the calculator key-layout, but ignores shift + alpha
	/// </summary>
	/// <param name="key">scancode</param>
	/// <returns>keycode</returns>
	uint8_t scancode_to_key_raw(SDL_Event* _event);
};
#endif
