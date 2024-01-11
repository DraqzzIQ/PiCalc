#include "keyboard/SDLKeyboard.h"
#include "SDLKeyboard.h"
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
		case SDL_SCANCODE_A: return Chars::CHAR_TO_KEYCODE.at("A");
		case SDL_SCANCODE_B: return Chars::CHAR_TO_KEYCODE.at("B");
		case SDL_SCANCODE_C: return Chars::CHAR_TO_KEYCODE.at("C");
		case SDL_SCANCODE_D: return Chars::CHAR_TO_KEYCODE.at("D");
		case SDL_SCANCODE_E: return Chars::CHAR_TO_KEYCODE.at("E");
		case SDL_SCANCODE_F: return Chars::CHAR_TO_KEYCODE.at("F");
		case SDL_SCANCODE_G: return Chars::CHAR_TO_KEYCODE.at("G");
		case SDL_SCANCODE_H: return Chars::CHAR_TO_KEYCODE.at("H");
		case SDL_SCANCODE_I: return Chars::CHAR_TO_KEYCODE.at("I");
		case SDL_SCANCODE_J: return Chars::CHAR_TO_KEYCODE.at("J");
		case SDL_SCANCODE_K: return Chars::CHAR_TO_KEYCODE.at("K");
		case SDL_SCANCODE_L: return Chars::CHAR_TO_KEYCODE.at("L");
		case SDL_SCANCODE_M: return Chars::CHAR_TO_KEYCODE.at("M");
		case SDL_SCANCODE_N: return Chars::CHAR_TO_KEYCODE.at("N");
		case SDL_SCANCODE_O: return Chars::CHAR_TO_KEYCODE.at("O");
		case SDL_SCANCODE_P: return Chars::CHAR_TO_KEYCODE.at("P");
		case SDL_SCANCODE_Q: return Chars::CHAR_TO_KEYCODE.at("Q");
		case SDL_SCANCODE_R: return Chars::CHAR_TO_KEYCODE.at("R");
		case SDL_SCANCODE_S: return Chars::CHAR_TO_KEYCODE.at("S");
		case SDL_SCANCODE_T: return Chars::CHAR_TO_KEYCODE.at("T");
		case SDL_SCANCODE_U: return Chars::CHAR_TO_KEYCODE.at("U");
		case SDL_SCANCODE_V: return Chars::CHAR_TO_KEYCODE.at("V");
		case SDL_SCANCODE_W: return Chars::CHAR_TO_KEYCODE.at("W");
		case SDL_SCANCODE_X: return Chars::CHAR_TO_KEYCODE.at("X");
		case SDL_SCANCODE_Y: return Chars::CHAR_TO_KEYCODE.at("Z");
		case SDL_SCANCODE_Z: return Chars::CHAR_TO_KEYCODE.at("Y");
		// everything else
		case SDL_SCANCODE_7: return Chars::CHAR_TO_KEYCODE.at("/");
		case SDL_SCANCODE_KP_DIVIDE: return Chars::CHAR_TO_KEYCODE.at("/");
		case SDL_SCANCODE_8: return Chars::CHAR_TO_KEYCODE.at("(");
		case SDL_SCANCODE_9: return Chars::CHAR_TO_KEYCODE.at(")");
		case SDL_SCANCODE_RIGHTBRACKET: return Chars::CHAR_TO_KEYCODE.at("*");
		case SDL_SCANCODE_MINUS: return Chars::CHAR_TO_KEYCODE.at("?");
		case SDL_SCANCODE_1: return Chars::CHAR_TO_KEYCODE.at("!");
		case SDL_SCANCODE_COMMA: return Chars::CHAR_TO_KEYCODE.at(";");
		case SDL_SCANCODE_PERIOD: return Chars::CHAR_TO_KEYCODE.at(":");
		case SDL_SCANCODE_5: return Chars::CHAR_TO_KEYCODE.at("%");
		case SDL_SCANCODE_4: return Chars::CHAR_TO_KEYCODE.at("$");
		case SDL_SCANCODE_0: return Chars::CHAR_TO_KEYCODE.at("=");
		case SDL_SCANCODE_2: return Chars::CHAR_TO_KEYCODE.at("\"");
		case SDL_SCANCODE_BACKSLASH: return Chars::CHAR_TO_KEYCODE.at("'");
		case SDL_SCANCODE_6: return Chars::CHAR_TO_KEYCODE.at("&");
		case SDL_SCANCODE_NONUSBACKSLASH: return Chars::CHAR_TO_KEYCODE.at(">");
		case SDL_SCANCODE_SLASH: return Chars::CHAR_TO_KEYCODE.at("_");

		// default
		default: return Chars::CHAR_TO_KEYCODE.at("unknown");
		}
	} else if (is_ralt_active()) {
		switch (_event->key.keysym.scancode) {
		case SDL_SCANCODE_NONUSBACKSLASH: return Chars::CHAR_TO_KEYCODE.at("|");
		case SDL_SCANCODE_7: return Chars::CHAR_TO_KEYCODE.at("{");
		case SDL_SCANCODE_0: return Chars::CHAR_TO_KEYCODE.at("}");
		case SDL_SCANCODE_8: return Chars::CHAR_TO_KEYCODE.at("[");
		case SDL_SCANCODE_9: return Chars::CHAR_TO_KEYCODE.at("]");
		case SDL_SCANCODE_MINUS: return Chars::CHAR_TO_KEYCODE.at("\\");
		case SDL_SCANCODE_Q: return Chars::CHAR_TO_KEYCODE.at("@");
		case SDL_SCANCODE_RIGHTBRACKET: return Chars::CHAR_TO_KEYCODE.at("~");

		default: return Chars::CHAR_TO_KEYCODE.at("unknown");
		}
	} else {
		switch (_event->key.keysym.scancode) {
		// Numbers
		case SDL_SCANCODE_1: return Chars::CHAR_TO_KEYCODE.at("1");
		case SDL_SCANCODE_2: return Chars::CHAR_TO_KEYCODE.at("2");
		case SDL_SCANCODE_3: return Chars::CHAR_TO_KEYCODE.at("3");
		case SDL_SCANCODE_4: return Chars::CHAR_TO_KEYCODE.at("4");
		case SDL_SCANCODE_5: return Chars::CHAR_TO_KEYCODE.at("5");
		case SDL_SCANCODE_6: return Chars::CHAR_TO_KEYCODE.at("6");
		case SDL_SCANCODE_7: return Chars::CHAR_TO_KEYCODE.at("7");
		case SDL_SCANCODE_8: return Chars::CHAR_TO_KEYCODE.at("8");
		case SDL_SCANCODE_9: return Chars::CHAR_TO_KEYCODE.at("9");
		case SDL_SCANCODE_0: return Chars::CHAR_TO_KEYCODE.at("0");
		// Keypad Numbers
		case SDL_SCANCODE_KP_1: return Chars::CHAR_TO_KEYCODE.at("1");
		case SDL_SCANCODE_KP_2: return Chars::CHAR_TO_KEYCODE.at("2");
		case SDL_SCANCODE_KP_3: return Chars::CHAR_TO_KEYCODE.at("3");
		case SDL_SCANCODE_KP_4: return Chars::CHAR_TO_KEYCODE.at("4");
		case SDL_SCANCODE_KP_5: return Chars::CHAR_TO_KEYCODE.at("5");
		case SDL_SCANCODE_KP_6: return Chars::CHAR_TO_KEYCODE.at("6");
		case SDL_SCANCODE_KP_7: return Chars::CHAR_TO_KEYCODE.at("7");
		case SDL_SCANCODE_KP_8: return Chars::CHAR_TO_KEYCODE.at("8");
		case SDL_SCANCODE_KP_9: return Chars::CHAR_TO_KEYCODE.at("9");
		case SDL_SCANCODE_KP_0: return Chars::CHAR_TO_KEYCODE.at("0");
		// Letters
		case SDL_SCANCODE_A: return Chars::CHAR_TO_KEYCODE.at("a");
		case SDL_SCANCODE_B: return Chars::CHAR_TO_KEYCODE.at("b");
		case SDL_SCANCODE_C: return Chars::CHAR_TO_KEYCODE.at("c");
		case SDL_SCANCODE_D: return Chars::CHAR_TO_KEYCODE.at("d");
		case SDL_SCANCODE_E: return Chars::CHAR_TO_KEYCODE.at("e");
		case SDL_SCANCODE_F: return Chars::CHAR_TO_KEYCODE.at("f");
		case SDL_SCANCODE_G: return Chars::CHAR_TO_KEYCODE.at("g");
		case SDL_SCANCODE_H: return Chars::CHAR_TO_KEYCODE.at("h");
		case SDL_SCANCODE_I: return Chars::CHAR_TO_KEYCODE.at("i");
		case SDL_SCANCODE_J: return Chars::CHAR_TO_KEYCODE.at("j");
		case SDL_SCANCODE_K: return Chars::CHAR_TO_KEYCODE.at("k");
		case SDL_SCANCODE_L: return Chars::CHAR_TO_KEYCODE.at("l");
		case SDL_SCANCODE_M: return Chars::CHAR_TO_KEYCODE.at("m");
		case SDL_SCANCODE_N: return Chars::CHAR_TO_KEYCODE.at("n");
		case SDL_SCANCODE_O: return Chars::CHAR_TO_KEYCODE.at("o");
		case SDL_SCANCODE_P: return Chars::CHAR_TO_KEYCODE.at("p");
		case SDL_SCANCODE_Q: return Chars::CHAR_TO_KEYCODE.at("q");
		case SDL_SCANCODE_R: return Chars::CHAR_TO_KEYCODE.at("r");
		case SDL_SCANCODE_S: return Chars::CHAR_TO_KEYCODE.at("s");
		case SDL_SCANCODE_T: return Chars::CHAR_TO_KEYCODE.at("t");
		case SDL_SCANCODE_U: return Chars::CHAR_TO_KEYCODE.at("u");
		case SDL_SCANCODE_V: return Chars::CHAR_TO_KEYCODE.at("v");
		case SDL_SCANCODE_W: return Chars::CHAR_TO_KEYCODE.at("w");
		case SDL_SCANCODE_X: return Chars::CHAR_TO_KEYCODE.at("x");
		case SDL_SCANCODE_Y: return Chars::CHAR_TO_KEYCODE.at("z");
		case SDL_SCANCODE_Z: return Chars::CHAR_TO_KEYCODE.at("y");
		// everything else
		case SDL_SCANCODE_LEFT: return Chars::CHAR_TO_KEYCODE.at("left");
		case SDL_SCANCODE_RIGHT: return Chars::CHAR_TO_KEYCODE.at("right");
		case SDL_SCANCODE_DOWN: return Chars::CHAR_TO_KEYCODE.at("down");
		case SDL_SCANCODE_UP: return Chars::CHAR_TO_KEYCODE.at("up");
		case SDL_SCANCODE_BACKSPACE: return Chars::CHAR_TO_KEYCODE.at("DEL");
		case SDL_SCANCODE_SPACE: return Chars::CHAR_TO_KEYCODE.at(" ");
		case SDL_SCANCODE_RETURN: return Chars::CHAR_TO_KEYCODE.at("RETURN");
		case SDL_SCANCODE_KP_DIVIDE: return Chars::CHAR_TO_KEYCODE.at("/");
		case SDL_SCANCODE_KP_MULTIPLY: return Chars::CHAR_TO_KEYCODE.at("*");
		case SDL_SCANCODE_KP_MINUS: return Chars::CHAR_TO_KEYCODE.at("-");
		case SDL_SCANCODE_KP_PLUS: return Chars::CHAR_TO_KEYCODE.at("+");
		case SDL_SCANCODE_RIGHTBRACKET: return Chars::CHAR_TO_KEYCODE.at("+");
		case SDL_SCANCODE_SLASH: return Chars::CHAR_TO_KEYCODE.at("-");
		case SDL_SCANCODE_COMMA: return Chars::CHAR_TO_KEYCODE.at(",");
		case SDL_SCANCODE_PERIOD: return Chars::CHAR_TO_KEYCODE.at(".");
		case SDL_SCANCODE_BACKSLASH: return Chars::CHAR_TO_KEYCODE.at("#");
		case SDL_SCANCODE_GRAVE: return Chars::CHAR_TO_KEYCODE.at("^");
		case SDL_SCANCODE_NONUSBACKSLASH: return Chars::CHAR_TO_KEYCODE.at("<");

		// default
		default: return Chars::CHAR_TO_KEYCODE.at("unknown");
		}
	}
}

KEY SDLKeyboard::scancode_to_key_raw(SDL_Event* _event)
{
	switch (_event->key.keysym.scancode) {
	case SDL_SCANCODE_RSHIFT: return Chars::CHAR_TO_KEYCODE.at("SHIFT");
	case SDL_SCANCODE_LSHIFT: return Chars::CHAR_TO_KEYCODE.at("SHIFT");
	case SDL_SCANCODE_A: return Chars::CHAR_TO_KEYCODE.at("Abs");
	case SDL_SCANCODE_F: return Chars::CHAR_TO_KEYCODE.at("fraction");
	case SDL_SCANCODE_N: return Chars::CHAR_TO_KEYCODE.at("(-)");
	case SDL_SCANCODE_R: return Chars::CHAR_TO_KEYCODE.at("RCL");
	case SDL_SCANCODE_7: return Chars::CHAR_TO_KEYCODE.at("7");
	case SDL_SCANCODE_4: return Chars::CHAR_TO_KEYCODE.at("4");
	case SDL_SCANCODE_1: return Chars::CHAR_TO_KEYCODE.at("1");
	case SDL_SCANCODE_0: return Chars::CHAR_TO_KEYCODE.at("0");
	case SDL_SCANCODE_RALT: return Chars::CHAR_TO_KEYCODE.at("ALPHA");
	case SDL_SCANCODE_LALT: return Chars::CHAR_TO_KEYCODE.at("ALPHA");
	case SDL_SCANCODE_F3: return Chars::CHAR_TO_KEYCODE.at("x^3");
	case SDL_SCANCODE_F6: return Chars::CHAR_TO_KEYCODE.at("root2");
	case SDL_SCANCODE_D: return Chars::CHAR_TO_KEYCODE.at("time");
	case SDL_SCANCODE_E: return Chars::CHAR_TO_KEYCODE.at("ENG");
	case SDL_SCANCODE_8: return Chars::CHAR_TO_KEYCODE.at("8");
	case SDL_SCANCODE_5: return Chars::CHAR_TO_KEYCODE.at("5");
	case SDL_SCANCODE_2: return Chars::CHAR_TO_KEYCODE.at("2");
	case SDL_SCANCODE_COMMA: return Chars::CHAR_TO_KEYCODE.at(",");
	case SDL_SCANCODE_LEFT: return Chars::CHAR_TO_KEYCODE.at("left");
	case SDL_SCANCODE_DOWN: return Chars::CHAR_TO_KEYCODE.at("down");
	case SDL_SCANCODE_F2: return Chars::CHAR_TO_KEYCODE.at("x^2");
	case SDL_SCANCODE_H: return Chars::CHAR_TO_KEYCODE.at("hyp");
	case SDL_SCANCODE_F7: return Chars::CHAR_TO_KEYCODE.at("(");
	case SDL_SCANCODE_9: return Chars::CHAR_TO_KEYCODE.at("9");
	case SDL_SCANCODE_6: return Chars::CHAR_TO_KEYCODE.at("6");
	case SDL_SCANCODE_3: return Chars::CHAR_TO_KEYCODE.at("3");
	case SDL_SCANCODE_X: return Chars::CHAR_TO_KEYCODE.at("*10^n");
	case SDL_SCANCODE_RIGHT: return Chars::CHAR_TO_KEYCODE.at("right");
	case SDL_SCANCODE_F1: return Chars::CHAR_TO_KEYCODE.at("x^-1");
	case SDL_SCANCODE_F4: return Chars::CHAR_TO_KEYCODE.at("x^n");
	case SDL_SCANCODE_S: return Chars::CHAR_TO_KEYCODE.at("sin");
	case SDL_SCANCODE_F8: return Chars::CHAR_TO_KEYCODE.at(")");
	case SDL_SCANCODE_BACKSPACE: return Chars::CHAR_TO_KEYCODE.at("DEL");
	case SDL_SCANCODE_PERIOD: return Chars::CHAR_TO_KEYCODE.at("multiply"); // .
	case SDL_SCANCODE_RIGHTBRACKET: return Chars::CHAR_TO_KEYCODE.at("+");  // +
	case SDL_SCANCODE_INSERT: return Chars::CHAR_TO_KEYCODE.at("Ans");
	case SDL_SCANCODE_UP: return Chars::CHAR_TO_KEYCODE.at("up");
	case SDL_SCANCODE_F9: return Chars::CHAR_TO_KEYCODE.at("logn");
	case SDL_SCANCODE_F10: return Chars::CHAR_TO_KEYCODE.at("log10");
	case SDL_SCANCODE_C: return Chars::CHAR_TO_KEYCODE.at("cos");
	case SDL_SCANCODE_TAB: return Chars::CHAR_TO_KEYCODE.at("S<>D");
	case SDL_SCANCODE_ESCAPE: return Chars::CHAR_TO_KEYCODE.at("AC");
	case SDL_SCANCODE_BACKSLASH: return Chars::CHAR_TO_KEYCODE.at("divide"); // #
	case SDL_SCANCODE_SLASH: return Chars::CHAR_TO_KEYCODE.at("-");          // -
	case SDL_SCANCODE_RETURN: return Chars::CHAR_TO_KEYCODE.at("=");
	case SDL_SCANCODE_LCTRL: return Chars::CHAR_TO_KEYCODE.at("MODE");
	case SDL_SCANCODE_RCTRL: return Chars::CHAR_TO_KEYCODE.at("MODE");
	case SDL_SCANCODE_F11: return Chars::CHAR_TO_KEYCODE.at("ln");
	case SDL_SCANCODE_T: return Chars::CHAR_TO_KEYCODE.at("tan");
	case SDL_SCANCODE_M: return Chars::CHAR_TO_KEYCODE.at("M+");
	default: return Chars::CHAR_TO_KEYCODE.at("unknown");
	}
}
#endif
