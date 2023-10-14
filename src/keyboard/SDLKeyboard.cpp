#include "keyboard/SDLKeyboard.h"
#ifndef PICO

SDLKeyboard::SDLKeyboard(WindowManager* window_manager): IKeyboard(window_manager)
{
	_event = new SDL_Event();
	sdl_init();
}

void SDLKeyboard::sdl_init()
{
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

void SDLKeyboard::check_for_keyboard_presses()
{
	if (SDL_PollEvent(_event)) {
		if (_event->type == SDL_QUIT) {
			SDL_DestroyWindow(_window);
			SDL_Quit();
			exit(0);
		} else if (_event->type == SDL_KEYDOWN) {
			_window_manager->handle_key_down(sdl_event_to_keypress(_event));
		} else if (_event->type == SDL_KEYUP) {
			_window_manager->handle_key_up(sdl_event_to_keypress(_event));
		}
	}
}

KeyPress SDLKeyboard::sdl_event_to_keypress(SDL_Event* _event)
{
	KeyPress keypress = KeyPress();
	keypress.shift = is_shift_active();
	keypress.alpha = is_alpha_active();
	keypress.key_raw = scancode_to_key_raw(_event);
	keypress.key_calculator = raw_key_to_calculator_key(keypress.key_raw, keypress.shift, keypress.alpha);
	keypress.key_keyboard = scancode_to_key_keyboard(_event);

	std::cout << unsigned(keypress.key_raw) << "        ";
	// std::cout << unsigned(_event->key.keysym.scancode);

	return keypress;
}

uint8_t SDLKeyboard::scancode_to_key_keyboard(SDL_Event* _event)
{
	if (is_shift_active()) {
		switch (_event->key.keysym.scancode) {
			// letters
		case SDL_SCANCODE_A: return Chars::KEY_MAP.at("A");
		case SDL_SCANCODE_B: return Chars::KEY_MAP.at("B");
		case SDL_SCANCODE_C: return Chars::KEY_MAP.at("C");
		case SDL_SCANCODE_D: return Chars::KEY_MAP.at("D");
		case SDL_SCANCODE_E: return Chars::KEY_MAP.at("E");
		case SDL_SCANCODE_F: return Chars::KEY_MAP.at("F");
		case SDL_SCANCODE_G: return Chars::KEY_MAP.at("G");
		case SDL_SCANCODE_H: return Chars::KEY_MAP.at("H");
		case SDL_SCANCODE_I: return Chars::KEY_MAP.at("I");
		case SDL_SCANCODE_J: return Chars::KEY_MAP.at("J");
		case SDL_SCANCODE_K: return Chars::KEY_MAP.at("K");
		case SDL_SCANCODE_L: return Chars::KEY_MAP.at("L");
		case SDL_SCANCODE_M: return Chars::KEY_MAP.at("M");
		case SDL_SCANCODE_N: return Chars::KEY_MAP.at("N");
		case SDL_SCANCODE_O: return Chars::KEY_MAP.at("O");
		case SDL_SCANCODE_P: return Chars::KEY_MAP.at("P");
		case SDL_SCANCODE_Q: return Chars::KEY_MAP.at("Q");
		case SDL_SCANCODE_R: return Chars::KEY_MAP.at("R");
		case SDL_SCANCODE_S: return Chars::KEY_MAP.at("S");
		case SDL_SCANCODE_T: return Chars::KEY_MAP.at("T");
		case SDL_SCANCODE_U: return Chars::KEY_MAP.at("U");
		case SDL_SCANCODE_V: return Chars::KEY_MAP.at("V");
		case SDL_SCANCODE_W: return Chars::KEY_MAP.at("W");
		case SDL_SCANCODE_X: return Chars::KEY_MAP.at("X");
		case SDL_SCANCODE_Y: return Chars::KEY_MAP.at("Y");
		case SDL_SCANCODE_Z:
			return Chars::KEY_MAP.at("Z");
			// everything else
		case SDL_SCANCODE_7: return Chars::KEY_MAP.at("fraction");
		case SDL_SCANCODE_KP_DIVIDE: return Chars::KEY_MAP.at("fraction");
		case SDL_SCANCODE_8: return Chars::KEY_MAP.at("(");
		case SDL_SCANCODE_9: return Chars::KEY_MAP.at(")");
		case 48:
			return Chars::KEY_MAP.at("*");
			// default
		default: return Chars::KEY_MAP.at("unknown");
		}
	} else {
		switch (_event->key.keysym.scancode) {
			// Numbers
		case SDL_SCANCODE_1: return Chars::KEY_MAP.at("1");
		case SDL_SCANCODE_2: return Chars::KEY_MAP.at("2");
		case SDL_SCANCODE_3: return Chars::KEY_MAP.at("3");
		case SDL_SCANCODE_4: return Chars::KEY_MAP.at("4");
		case SDL_SCANCODE_5: return Chars::KEY_MAP.at("5");
		case SDL_SCANCODE_6: return Chars::KEY_MAP.at("6");
		case SDL_SCANCODE_7: return Chars::KEY_MAP.at("7");
		case SDL_SCANCODE_8: return Chars::KEY_MAP.at("8");
		case SDL_SCANCODE_9: return Chars::KEY_MAP.at("9");
		case SDL_SCANCODE_0:
			return Chars::KEY_MAP.at("0");
			// Keypad Numbers
		case SDL_SCANCODE_KP_1: return Chars::KEY_MAP.at("1");
		case SDL_SCANCODE_KP_2: return Chars::KEY_MAP.at("2");
		case SDL_SCANCODE_KP_3: return Chars::KEY_MAP.at("3");
		case SDL_SCANCODE_KP_4: return Chars::KEY_MAP.at("4");
		case SDL_SCANCODE_KP_5: return Chars::KEY_MAP.at("5");
		case SDL_SCANCODE_KP_6: return Chars::KEY_MAP.at("6");
		case SDL_SCANCODE_KP_7: return Chars::KEY_MAP.at("7");
		case SDL_SCANCODE_KP_8: return Chars::KEY_MAP.at("8");
		case SDL_SCANCODE_KP_9: return Chars::KEY_MAP.at("9");
		case SDL_SCANCODE_KP_0:
			return Chars::KEY_MAP.at("0");
			// Letters
		case SDL_SCANCODE_A: return Chars::KEY_MAP.at("a");
		case SDL_SCANCODE_B: return Chars::KEY_MAP.at("b");
		case SDL_SCANCODE_C: return Chars::KEY_MAP.at("c");
		case SDL_SCANCODE_D: return Chars::KEY_MAP.at("d");
		case SDL_SCANCODE_E: return Chars::KEY_MAP.at("e");
		case SDL_SCANCODE_F: return Chars::KEY_MAP.at("f");
		case SDL_SCANCODE_G: return Chars::KEY_MAP.at("g");
		case SDL_SCANCODE_H: return Chars::KEY_MAP.at("h");
		case SDL_SCANCODE_I: return Chars::KEY_MAP.at("i");
		case SDL_SCANCODE_J: return Chars::KEY_MAP.at("j");
		case SDL_SCANCODE_K: return Chars::KEY_MAP.at("k");
		case SDL_SCANCODE_L: return Chars::KEY_MAP.at("l");
		case SDL_SCANCODE_M: return Chars::KEY_MAP.at("m");
		case SDL_SCANCODE_N: return Chars::KEY_MAP.at("n");
		case SDL_SCANCODE_O: return Chars::KEY_MAP.at("o");
		case SDL_SCANCODE_P: return Chars::KEY_MAP.at("p");
		case SDL_SCANCODE_Q: return Chars::KEY_MAP.at("q");
		case SDL_SCANCODE_R: return Chars::KEY_MAP.at("r");
		case SDL_SCANCODE_S: return Chars::KEY_MAP.at("s");
		case SDL_SCANCODE_T: return Chars::KEY_MAP.at("t");
		case SDL_SCANCODE_U: return Chars::KEY_MAP.at("u");
		case SDL_SCANCODE_V: return Chars::KEY_MAP.at("v");
		case SDL_SCANCODE_W: return Chars::KEY_MAP.at("w");
		case SDL_SCANCODE_X: return Chars::KEY_MAP.at("x");
		case SDL_SCANCODE_Y: return Chars::KEY_MAP.at("y");
		case SDL_SCANCODE_Z:
			return Chars::KEY_MAP.at("z");
			// everything else
		case SDL_SCANCODE_LEFT: return Chars::KEY_MAP.at("left");
		case SDL_SCANCODE_RIGHT: return Chars::KEY_MAP.at("right");
		case SDL_SCANCODE_DOWN: return Chars::KEY_MAP.at("down");
		case SDL_SCANCODE_UP: return Chars::KEY_MAP.at("up");
		case SDL_SCANCODE_BACKSPACE: return Chars::KEY_MAP.at("DEL");
		case SDL_SCANCODE_KP_DIVIDE: return Chars::KEY_MAP.at("/");
		case SDL_SCANCODE_KP_MULTIPLY: return Chars::KEY_MAP.at("*");
		case SDL_SCANCODE_KP_MINUS: return Chars::KEY_MAP.at("-");
		case SDL_SCANCODE_KP_PLUS: return Chars::KEY_MAP.at("+");
		case 48: return Chars::KEY_MAP.at("+");
		case 56:
			return Chars::KEY_MAP.at("-");
			// default
		default: return Chars::KEY_MAP.at("unknown");
		}
	}
}

uint8_t SDLKeyboard::scancode_to_key_raw(SDL_Event* _event)
{
	switch (_event->key.keysym.scancode) {
	case SDL_SCANCODE_RSHIFT: return Chars::KEY_MAP.at("SHIFT");
	case SDL_SCANCODE_LSHIFT: return Chars::KEY_MAP.at("SHIFT");
	case SDL_SCANCODE_A: return Chars::KEY_MAP.at("Abs");
	case SDL_SCANCODE_F: return Chars::KEY_MAP.at("fraction");
	case SDL_SCANCODE_N: return Chars::KEY_MAP.at("(-)");
	case SDL_SCANCODE_R: return Chars::KEY_MAP.at("RCL");
	case SDL_SCANCODE_7: return Chars::KEY_MAP.at("7");
	case SDL_SCANCODE_4: return Chars::KEY_MAP.at("4");
	case SDL_SCANCODE_1: return Chars::KEY_MAP.at("1");
	case SDL_SCANCODE_0: return Chars::KEY_MAP.at("0");
	case SDL_SCANCODE_RALT: return Chars::KEY_MAP.at("ALPHA");
	case SDL_SCANCODE_LALT: return Chars::KEY_MAP.at("ALPHA");
	case SDL_SCANCODE_F3: return Chars::KEY_MAP.at("x^3");
	case SDL_SCANCODE_F6: return Chars::KEY_MAP.at("root2");
	case SDL_SCANCODE_D: return Chars::KEY_MAP.at("time");
	case SDL_SCANCODE_E: return Chars::KEY_MAP.at("ENG");
	case SDL_SCANCODE_8: return Chars::KEY_MAP.at("8");
	case SDL_SCANCODE_5: return Chars::KEY_MAP.at("5");
	case SDL_SCANCODE_2: return Chars::KEY_MAP.at("2");
	case SDL_SCANCODE_COMMA: return Chars::KEY_MAP.at(",");
	case SDL_SCANCODE_LEFT: return Chars::KEY_MAP.at("left");
	case SDL_SCANCODE_DOWN: return Chars::KEY_MAP.at("down");
	case SDL_SCANCODE_F2: return Chars::KEY_MAP.at("x^2");
	case SDL_SCANCODE_H: return Chars::KEY_MAP.at("hyp");
	case SDL_SCANCODE_F7: return Chars::KEY_MAP.at("(");
	case SDL_SCANCODE_9: return Chars::KEY_MAP.at("9");
	case SDL_SCANCODE_6: return Chars::KEY_MAP.at("6");
	case SDL_SCANCODE_3: return Chars::KEY_MAP.at("3");
	case SDL_SCANCODE_X: return Chars::KEY_MAP.at("*10^n");
	case SDL_SCANCODE_RIGHT: return Chars::KEY_MAP.at("right");
	case SDL_SCANCODE_F1: return Chars::KEY_MAP.at("x^-1");
	case SDL_SCANCODE_F4: return Chars::KEY_MAP.at("x^n");
	case SDL_SCANCODE_S: return Chars::KEY_MAP.at("sin");
	case SDL_SCANCODE_F8: return Chars::KEY_MAP.at(")");
	case SDL_SCANCODE_BACKSPACE: return Chars::KEY_MAP.at("DEL");
	case SDL_SCANCODE_PERIOD: return Chars::KEY_MAP.at("multiply"); // .
	case 48: return Chars::KEY_MAP.at("+");                         // +
	case SDL_SCANCODE_INSERT: return Chars::KEY_MAP.at("Ans");
	case SDL_SCANCODE_UP: return Chars::KEY_MAP.at("up");
	case SDL_SCANCODE_F9: return Chars::KEY_MAP.at("logn");
	case SDL_SCANCODE_F10: return Chars::KEY_MAP.at("log10");
	case SDL_SCANCODE_C: return Chars::KEY_MAP.at("cos");
	case SDL_SCANCODE_TAB: return Chars::KEY_MAP.at("S<>D");
	case SDL_SCANCODE_ESCAPE: return Chars::KEY_MAP.at("AC");
	case 49: return Chars::KEY_MAP.at("divide"); // #
	case 56: return Chars::KEY_MAP.at("-");      // -
	case SDL_SCANCODE_RETURN: return Chars::KEY_MAP.at("=");
	case SDL_SCANCODE_LCTRL: return Chars::KEY_MAP.at("MODE");
	case SDL_SCANCODE_RCTRL: return Chars::KEY_MAP.at("MODE");
	case SDL_SCANCODE_F11: return Chars::KEY_MAP.at("ln");
	case SDL_SCANCODE_T: return Chars::KEY_MAP.at("tan");
	case SDL_SCANCODE_M: return Chars::KEY_MAP.at("M+");
	default: return Chars::KEY_MAP.at("unknown");
	}
}
#endif