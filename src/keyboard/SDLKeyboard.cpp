#include "keyboard/SDLKeyboard.h"
#ifndef PICO

SDLKeyboard::SDLKeyboard():
	IKeyboard()
{
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
	return SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LALT];
}

bool SDLKeyboard::is_ralt_active()
{
	return SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RALT];
}

void SDLKeyboard::check_for_keyboard_presses()
{
	if (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_QUIT) {
			SDL_DestroyWindow(_window);
			SDL_Quit();
			exit(0);
		} else if (_event.type == SDL_KEYDOWN) {
			_window_manager->handle_key_down(sdl_event_to_keypress(&_event));
		} else if (_event.type == SDL_KEYUP) {
			_window_manager->handle_key_up(sdl_event_to_keypress(&_event));
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

	// std::cout << unsigned(keypress.key_raw) << "        ";
	//  std::cout << unsigned(_event->key.keysym.scancode);

	return keypress;
}

KEY SDLKeyboard::scancode_to_key_keyboard(SDL_Event* _event)
{
	if (is_shift_active()) {
		switch (_event->key.keysym.scancode) {
		// letters
		case SDL_SCANCODE_A: return 'A';
		case SDL_SCANCODE_B: return 'B';
		case SDL_SCANCODE_C: return 'C';
		case SDL_SCANCODE_D: return 'D';
		case SDL_SCANCODE_E: return 'E';
		case SDL_SCANCODE_F: return 'F';
		case SDL_SCANCODE_G: return 'G';
		case SDL_SCANCODE_H: return 'H';
		case SDL_SCANCODE_I: return 'I';
		case SDL_SCANCODE_J: return 'J';
		case SDL_SCANCODE_K: return 'K';
		case SDL_SCANCODE_L: return 'L';
		case SDL_SCANCODE_M: return 'M';
		case SDL_SCANCODE_N: return 'N';
		case SDL_SCANCODE_O: return 'O';
		case SDL_SCANCODE_P: return 'P';
		case SDL_SCANCODE_Q: return 'Q';
		case SDL_SCANCODE_R: return 'R';
		case SDL_SCANCODE_S: return 'S';
		case SDL_SCANCODE_T: return 'T';
		case SDL_SCANCODE_U: return 'U';
		case SDL_SCANCODE_V: return 'V';
		case SDL_SCANCODE_W: return 'W';
		case SDL_SCANCODE_X: return 'X';
		case SDL_SCANCODE_Y: return 'Z';
		case SDL_SCANCODE_Z: return 'Y';
		// everything else
		case SDL_SCANCODE_7: return '/';
		case SDL_SCANCODE_KP_DIVIDE: return '/';
		case SDL_SCANCODE_8: return '(';
		case SDL_SCANCODE_9: return ')';
		case SDL_SCANCODE_RIGHTBRACKET: return '*';
		case SDL_SCANCODE_MINUS: return '?';
		case SDL_SCANCODE_1: return '!';
		case SDL_SCANCODE_COMMA: return ';';
		case SDL_SCANCODE_PERIOD: return ':';
		case SDL_SCANCODE_5: return '%';
		case SDL_SCANCODE_4: return '$';
		case SDL_SCANCODE_0: return '=';
		case SDL_SCANCODE_2: return '\"';
		case SDL_SCANCODE_BACKSLASH: return '\'';
		case SDL_SCANCODE_6: return '&';
		case SDL_SCANCODE_NONUSBACKSLASH: return '>';
		case SDL_SCANCODE_SLASH: return '_';
		// default
		default: return 0;
		}
	} else if (is_ralt_active()) {
		switch (_event->key.keysym.scancode) {
		case SDL_SCANCODE_NONUSBACKSLASH: return '|';
		case SDL_SCANCODE_7: return '{';
		case SDL_SCANCODE_0: return '}';
		case SDL_SCANCODE_8: return '[';
		case SDL_SCANCODE_9: return ']';
		case SDL_SCANCODE_MINUS: return '\\';
		case SDL_SCANCODE_Q: return '@';
		case SDL_SCANCODE_E: return KEY_EURO;
		case SDL_SCANCODE_RIGHTBRACKET: return '~';
		default: return 0;
		}
	} else {
		switch (_event->key.keysym.scancode) {
		// Numbers
		case SDL_SCANCODE_1: return '1';
		case SDL_SCANCODE_2: return '2';
		case SDL_SCANCODE_3: return '3';
		case SDL_SCANCODE_4: return '4';
		case SDL_SCANCODE_5: return '5';
		case SDL_SCANCODE_6: return '6';
		case SDL_SCANCODE_7: return '7';
		case SDL_SCANCODE_8: return '8';
		case SDL_SCANCODE_9: return '9';
		case SDL_SCANCODE_0: return '0';
		// Keypad Numbers
		case SDL_SCANCODE_KP_1: return '1';
		case SDL_SCANCODE_KP_2: return '2';
		case SDL_SCANCODE_KP_3: return '3';
		case SDL_SCANCODE_KP_4: return '4';
		case SDL_SCANCODE_KP_5: return '5';
		case SDL_SCANCODE_KP_6: return '6';
		case SDL_SCANCODE_KP_7: return '7';
		case SDL_SCANCODE_KP_8: return '8';
		case SDL_SCANCODE_KP_9: return '9';
		case SDL_SCANCODE_KP_0: return '0';
		// Letters
		case SDL_SCANCODE_A: return 'a';
		case SDL_SCANCODE_B: return 'b';
		case SDL_SCANCODE_C: return 'c';
		case SDL_SCANCODE_D: return 'd';
		case SDL_SCANCODE_E: return 'e';
		case SDL_SCANCODE_F: return 'f';
		case SDL_SCANCODE_G: return 'g';
		case SDL_SCANCODE_H: return 'h';
		case SDL_SCANCODE_I: return 'i';
		case SDL_SCANCODE_J: return 'j';
		case SDL_SCANCODE_K: return 'k';
		case SDL_SCANCODE_L: return 'l';
		case SDL_SCANCODE_M: return 'm';
		case SDL_SCANCODE_N: return 'n';
		case SDL_SCANCODE_O: return 'o';
		case SDL_SCANCODE_P: return 'p';
		case SDL_SCANCODE_Q: return 'q';
		case SDL_SCANCODE_R: return 'r';
		case SDL_SCANCODE_S: return 's';
		case SDL_SCANCODE_T: return 't';
		case SDL_SCANCODE_U: return 'u';
		case SDL_SCANCODE_V: return 'v';
		case SDL_SCANCODE_W: return 'w';
		case SDL_SCANCODE_X: return 'x';
		case SDL_SCANCODE_Y: return 'z';
		case SDL_SCANCODE_Z: return 'y';
		// everything else
		case SDL_SCANCODE_LEFT: return KEY_LEFT;
		case SDL_SCANCODE_RIGHT: return KEY_RIGHT;
		case SDL_SCANCODE_DOWN: return KEY_DOWN;
		case SDL_SCANCODE_UP: return KEY_UP;
		case SDL_SCANCODE_BACKSPACE: return KEY_DEL;
		case SDL_SCANCODE_ESCAPE: return KEY_AC;
		case SDL_SCANCODE_SPACE: return ' ';
		case SDL_SCANCODE_RETURN: return '\n';
		case SDL_SCANCODE_KP_DIVIDE: return '/';
		case SDL_SCANCODE_KP_MULTIPLY: return '*';
		case SDL_SCANCODE_KP_MINUS: return '-';
		case SDL_SCANCODE_KP_PLUS: return '+';
		case SDL_SCANCODE_RIGHTBRACKET: return '+';
		case SDL_SCANCODE_SLASH: return '-';
		case SDL_SCANCODE_COMMA: return ',';
		case SDL_SCANCODE_PERIOD: return '.';
		case SDL_SCANCODE_BACKSLASH: return '#';
		case SDL_SCANCODE_GRAVE: return '^';
		case SDL_SCANCODE_NONUSBACKSLASH: return '<';
		// default
		default: return 0;
		}
	}
}

KEY SDLKeyboard::scancode_to_key_raw(SDL_Event* _event)
{
	switch (_event->key.keysym.scancode) {
	case SDL_SCANCODE_RSHIFT: return KEY_SHIFT;
	case SDL_SCANCODE_LSHIFT: return KEY_SHIFT;
	case SDL_SCANCODE_A: return KEY_ABS;
	case SDL_SCANCODE_F: return KEY_FRACTION;
	case SDL_SCANCODE_N: return KEY_NEGATE;
	case SDL_SCANCODE_R: return KEY_RCL;
	case SDL_SCANCODE_7: return '7';
	case SDL_SCANCODE_4: return '4';
	case SDL_SCANCODE_1: return '1';
	case SDL_SCANCODE_0: return '0';
	case SDL_SCANCODE_RALT: return KEY_ALPHA;
	case SDL_SCANCODE_LALT: return KEY_ALPHA;
	case SDL_SCANCODE_F3: return KEY_CUBED;
	case SDL_SCANCODE_F6: return KEY_SQRT;
	case SDL_SCANCODE_D: return KEY_TIME;
	case SDL_SCANCODE_E: return KEY_ENG;
	case SDL_SCANCODE_8: return '8';
	case SDL_SCANCODE_5: return '5';
	case SDL_SCANCODE_2: return '2';
	case SDL_SCANCODE_COMMA: return ',';
	case SDL_SCANCODE_LEFT: return KEY_LEFT;
	case SDL_SCANCODE_DOWN: return KEY_DOWN;
	case SDL_SCANCODE_F2: return KEY_SQUARED;
	case SDL_SCANCODE_H: return KEY_HYP;
	case SDL_SCANCODE_F7: return '(';
	case SDL_SCANCODE_9: return '9';
	case SDL_SCANCODE_6: return '6';
	case SDL_SCANCODE_3: return '3';
	case SDL_SCANCODE_X: return KEY_SCIENTIFIC_E;
	case SDL_SCANCODE_RIGHT: return KEY_RIGHT;
	case SDL_SCANCODE_F1: return KEY_RECIPROCAL;
	case SDL_SCANCODE_F4: return KEY_POWER;
	case SDL_SCANCODE_S: return KEY_SIN;
	case SDL_SCANCODE_F8: return ')';
	case SDL_SCANCODE_BACKSPACE: return KEY_DEL;
	case SDL_SCANCODE_PERIOD: return KEY_MULTIPLY;
	case SDL_SCANCODE_RIGHTBRACKET: return '+';
	case SDL_SCANCODE_INSERT: return KEY_ANS;
	case SDL_SCANCODE_UP: return KEY_UP;
	case SDL_SCANCODE_F9: return KEY_LOGN;
	case SDL_SCANCODE_F10: return KEY_LOG;
	case SDL_SCANCODE_C: return KEY_COS;
	case SDL_SCANCODE_TAB: return KEY_S_D;
	case SDL_SCANCODE_ESCAPE: return KEY_AC;
	case SDL_SCANCODE_BACKSLASH: return KEY_DIVIDE;
	case SDL_SCANCODE_SLASH: return '-';
	case SDL_SCANCODE_RETURN: return '=';
	case SDL_SCANCODE_LCTRL: return KEY_MODE;
	case SDL_SCANCODE_RCTRL: return KEY_MODE;
	case SDL_SCANCODE_F11: return KEY_LN;
	case SDL_SCANCODE_T: return KEY_TAN;
	case SDL_SCANCODE_M: return KEY_M_PLUS;
	default: return 0;
	}
}
#endif
