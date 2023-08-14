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
		case SDL_SCANCODE_A: return KEY_MAP.at("A");
		case SDL_SCANCODE_B: return KEY_MAP.at("B");
		case SDL_SCANCODE_C: return KEY_MAP.at("C");
		case SDL_SCANCODE_D: return KEY_MAP.at("D");
		case SDL_SCANCODE_E: return KEY_MAP.at("E");
		case SDL_SCANCODE_F: return KEY_MAP.at("F");
		case SDL_SCANCODE_G: return KEY_MAP.at("G");
		case SDL_SCANCODE_H: return KEY_MAP.at("H");
		case SDL_SCANCODE_I: return KEY_MAP.at("I");
		case SDL_SCANCODE_J: return KEY_MAP.at("J");
		case SDL_SCANCODE_K: return KEY_MAP.at("K");
		case SDL_SCANCODE_L: return KEY_MAP.at("L");
		case SDL_SCANCODE_M: return KEY_MAP.at("M");
		case SDL_SCANCODE_N: return KEY_MAP.at("N");
		case SDL_SCANCODE_O: return KEY_MAP.at("O");
		case SDL_SCANCODE_P: return KEY_MAP.at("P");
		case SDL_SCANCODE_Q: return KEY_MAP.at("Q");
		case SDL_SCANCODE_R: return KEY_MAP.at("R");
		case SDL_SCANCODE_S: return KEY_MAP.at("S");
		case SDL_SCANCODE_T: return KEY_MAP.at("T");
		case SDL_SCANCODE_U: return KEY_MAP.at("U");
		case SDL_SCANCODE_V: return KEY_MAP.at("V");
		case SDL_SCANCODE_W: return KEY_MAP.at("W");
		case SDL_SCANCODE_X: return KEY_MAP.at("X");
		case SDL_SCANCODE_Y: return KEY_MAP.at("Y");
		case SDL_SCANCODE_Z: return KEY_MAP.at("Z");
			// everything else
		case SDL_SCANCODE_7: return KEY_MAP.at("fraction");
		case SDL_SCANCODE_KP_DIVIDE: return KEY_MAP.at("fraction");
		case SDL_SCANCODE_8: return KEY_MAP.at("(");
		case SDL_SCANCODE_9: return KEY_MAP.at(")");
		case 48: return KEY_MAP.at("*");
            // default
        default: return KEY_MAP.at("0");
		}
	}
	else {
		switch (_event->key.keysym.scancode) {
			// Numbers
		case SDL_SCANCODE_1: return KEY_MAP.at("1");
		case SDL_SCANCODE_2: return KEY_MAP.at("2");
		case SDL_SCANCODE_3: return KEY_MAP.at("3");
		case SDL_SCANCODE_4: return KEY_MAP.at("4");
		case SDL_SCANCODE_5: return KEY_MAP.at("5");
		case SDL_SCANCODE_6: return KEY_MAP.at("6");
		case SDL_SCANCODE_7: return KEY_MAP.at("7");
		case SDL_SCANCODE_8: return KEY_MAP.at("8");
		case SDL_SCANCODE_9: return KEY_MAP.at("9");
		case SDL_SCANCODE_0: return KEY_MAP.at("0");
			// Keypad Numbers
		case SDL_SCANCODE_KP_1: return KEY_MAP.at("1");
		case SDL_SCANCODE_KP_2: return KEY_MAP.at("2");
		case SDL_SCANCODE_KP_3: return KEY_MAP.at("3");
		case SDL_SCANCODE_KP_4: return KEY_MAP.at("4");
		case SDL_SCANCODE_KP_5: return KEY_MAP.at("5");
		case SDL_SCANCODE_KP_6: return KEY_MAP.at("6");
		case SDL_SCANCODE_KP_7: return KEY_MAP.at("7");
		case SDL_SCANCODE_KP_8: return KEY_MAP.at("8");
		case SDL_SCANCODE_KP_9: return KEY_MAP.at("9");
		case SDL_SCANCODE_KP_0: return KEY_MAP.at("0");
			// Letters
		case SDL_SCANCODE_A: return KEY_MAP.at("a");
		case SDL_SCANCODE_B: return KEY_MAP.at("b");
		case SDL_SCANCODE_C: return KEY_MAP.at("c");
		case SDL_SCANCODE_D: return KEY_MAP.at("d");
		case SDL_SCANCODE_E: return KEY_MAP.at("e");
		case SDL_SCANCODE_F: return KEY_MAP.at("f");
		case SDL_SCANCODE_G: return KEY_MAP.at("g");
		case SDL_SCANCODE_H: return KEY_MAP.at("h");
		case SDL_SCANCODE_I: return KEY_MAP.at("i");
		case SDL_SCANCODE_J: return KEY_MAP.at("j");
		case SDL_SCANCODE_K: return KEY_MAP.at("k");
		case SDL_SCANCODE_L: return KEY_MAP.at("l");
		case SDL_SCANCODE_M: return KEY_MAP.at("m");
		case SDL_SCANCODE_N: return KEY_MAP.at("n");
		case SDL_SCANCODE_O: return KEY_MAP.at("o");
		case SDL_SCANCODE_P: return KEY_MAP.at("p");
		case SDL_SCANCODE_Q: return KEY_MAP.at("q");
		case SDL_SCANCODE_R: return KEY_MAP.at("r");
		case SDL_SCANCODE_S: return KEY_MAP.at("s");
		case SDL_SCANCODE_T: return KEY_MAP.at("t");
		case SDL_SCANCODE_U: return KEY_MAP.at("u");
		case SDL_SCANCODE_V: return KEY_MAP.at("v");
		case SDL_SCANCODE_W: return KEY_MAP.at("w");
		case SDL_SCANCODE_X: return KEY_MAP.at("x");
		case SDL_SCANCODE_Y: return KEY_MAP.at("y");
		case SDL_SCANCODE_Z: return KEY_MAP.at("z");
			// everything else
		case SDL_SCANCODE_LEFT: return KEY_MAP.at("left");
		case SDL_SCANCODE_RIGHT: return KEY_MAP.at("right");
		case SDL_SCANCODE_DOWN: return KEY_MAP.at("down");
		case SDL_SCANCODE_UP: return KEY_MAP.at("up");
		case SDL_SCANCODE_BACKSPACE: return KEY_MAP.at("del");
		case SDL_SCANCODE_KP_DIVIDE: return KEY_MAP.at("/");
		case SDL_SCANCODE_KP_MULTIPLY: return KEY_MAP.at("*");
		case SDL_SCANCODE_KP_MINUS: return KEY_MAP.at("-");
		case SDL_SCANCODE_KP_PLUS: return KEY_MAP.at("+");
		case 48: return KEY_MAP.at("+");
		case 56: return KEY_MAP.at("-");
			// default
		default: return KEY_MAP.at("0");
		}
	}
    return 0;
}
#endif