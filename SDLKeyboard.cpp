#include "SDLKeyboard.h"
#ifndef PICO

SDLKeyboard::SDLKeyboard(WindowManager *window_manager) : IKeyboard(window_manager)
{
    _event = new SDL_Event();
    sdl_init();
}

void SDLKeyboard::sdl_init(){
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("keyboard input, NEEDS TO BE IN FOCUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 200, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_SetWindowAlwaysOnTop(_window, SDL_TRUE);

	SDL_Renderer* renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

bool SDLKeyboard::is_shift_active()
{
	return SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LSHIFT] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RSHIFT];
}

bool SDLKeyboard::is_alpha_active()
{
	return SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LALT] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RALT];
}

void SDLKeyboard::check_for_keyboard_presses() {
	if (SDL_PollEvent(_event)) {
		if (_event->type == SDL_QUIT) {
			SDL_DestroyWindow(_window);
	        SDL_Quit();
	        exit(0);
		}
		else if (_event->type == SDL_KEYDOWN) {
			_window_manager->handle_key_down(sdl_event_to_keypress(_event));
		}
		else if (_event->type == SDL_KEYUP) {
			_window_manager->handle_key_up(sdl_event_to_keypress(_event));
		}
	}
}

KeyPress SDLKeyboard::sdl_event_to_keypress(SDL_Event* _event){
    KeyPress keypress = KeyPress();
    keypress.key = scancode_to_keycode(_event);
    keypress.alpha = is_alpha_active();
    keypress.shift = is_shift_active();

    return keypress;
}

uint8_t SDLKeyboard::scancode_to_keycode(SDL_Event* _event) {
	if (is_shift_active()) {
		switch (_event->key.keysym.scancode) {
			//letters
		case 4: return KEY_MAP.at("A");
		case 5: return KEY_MAP.at("B");
		case 6: return KEY_MAP.at("C");
		case 7: return KEY_MAP.at("D");
		case 8: return KEY_MAP.at("E");
		case 9: return KEY_MAP.at("F");
		case 10: return KEY_MAP.at("G");
		case 11: return KEY_MAP.at("H");
		case 12: return KEY_MAP.at("I");
		case 13: return KEY_MAP.at("J");
		case 14: return KEY_MAP.at("K");
		case 15: return KEY_MAP.at("L");
		case 16: return KEY_MAP.at("M");
		case 17: return KEY_MAP.at("N");
		case 18: return KEY_MAP.at("O");
		case 19: return KEY_MAP.at("P");
		case 20: return KEY_MAP.at("Q");
		case 21: return KEY_MAP.at("R");
		case 22: return KEY_MAP.at("S");
		case 23: return KEY_MAP.at("T");
		case 24: return KEY_MAP.at("U");
		case 25: return KEY_MAP.at("V");
		case 26: return KEY_MAP.at("W");
		case 27: return KEY_MAP.at("X");
		case 28: return KEY_MAP.at("Y");
		case 29: return KEY_MAP.at("Z");
			// everything else
		case 84: return KEY_MAP.at("fraction");
		case 36: return KEY_MAP.at("fraction");
		case 48: return KEY_MAP.at("*");
		case 37: return KEY_MAP.at("(");
		case 38: return KEY_MAP.at(")");
        //default
		default: return KEY_MAP.at("0");
		}
	}
	else {
		switch (_event->key.keysym.scancode) {
			// Numbers
		case 30: return KEY_MAP.at("1");
		case 31: return KEY_MAP.at("2");
		case 32: return KEY_MAP.at("3");
		case 33: return KEY_MAP.at("4");
		case 34: return KEY_MAP.at("5");
		case 35: return KEY_MAP.at("6");
		case 36: return KEY_MAP.at("7");
		case 37: return KEY_MAP.at("8");
		case 38: return KEY_MAP.at("9");
		case 39: return KEY_MAP.at("0");
			// Keypad Numbers
		case 89: return KEY_MAP.at("1");
		case 90: return KEY_MAP.at("2");
		case 91: return KEY_MAP.at("3");
		case 92: return KEY_MAP.at("4");
		case 93: return KEY_MAP.at("5");
		case 94: return KEY_MAP.at("6");
		case 95: return KEY_MAP.at("7");
		case 96: return KEY_MAP.at("8");
		case 97: return KEY_MAP.at("9");
		case 98: return KEY_MAP.at("0");
			// Letters
		case 4: return KEY_MAP.at("a");
		case 5: return KEY_MAP.at("b");
		case 6: return KEY_MAP.at("c");
		case 7: return KEY_MAP.at("d");
		case 8: return KEY_MAP.at("e");
		case 9: return KEY_MAP.at("f");
		case 10: return KEY_MAP.at("g");
		case 11: return KEY_MAP.at("h");
		case 12: return KEY_MAP.at("i");
		case 13: return KEY_MAP.at("j");
		case 14: return KEY_MAP.at("k");
		case 15: return KEY_MAP.at("l");
		case 16: return KEY_MAP.at("m");
		case 17: return KEY_MAP.at("n");
		case 18: return KEY_MAP.at("o");
		case 19: return KEY_MAP.at("p");
		case 20: return KEY_MAP.at("q");
		case 21: return KEY_MAP.at("r");
		case 22: return KEY_MAP.at("s");
		case 23: return KEY_MAP.at("t");
		case 24: return KEY_MAP.at("u");
		case 25: return KEY_MAP.at("v");
		case 26: return KEY_MAP.at("w");
		case 27: return KEY_MAP.at("x");
		case 28: return KEY_MAP.at("y");
		case 29: return KEY_MAP.at("z");
			// everything else
		case 79: return KEY_MAP.at("left");
		case 80: return KEY_MAP.at("right");
		case 81: return KEY_MAP.at("down");
		case 82: return KEY_MAP.at("up");
		case 42: return KEY_MAP.at("del");
		case 84: return KEY_MAP.at("/");
		case 85: return KEY_MAP.at("*");
		case 86: return KEY_MAP.at("-");
		case 87: return KEY_MAP.at("+");
		case 48: return KEY_MAP.at("+");
		case 56: return KEY_MAP.at("-");
			// default
		default: return KEY_MAP.at("0");
		}
	}
    return 0;
}
#endif