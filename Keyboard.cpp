#include "Keyboard.h"
#include "Chars.h"

Keyboard::Keyboard(WindowManager* window_manager)
{
	_window_manager = window_manager;
	sdl_init();

#if defined(_WIN32) || defined(__linux__)
	check_for_keyboard_events();
#else
	check_for_calc_button_presses();
#endif // _WIN32 || defined __linux__
}

int Keyboard::scancode_to_number(int scancode)
{
	if (scancode >= SDL_SCANCODE_1 && scancode <= SDL_SCANCODE_0) {
		if (scancode == SDL_SCANCODE_0) return 0;
		else return scancode - SDL_SCANCODE_1 + 1;
	}
	else if (scancode >= SDL_SCANCODE_KP_1 && scancode <= SDL_SCANCODE_KP_0) {
		if (scancode == SDL_SCANCODE_KP_0) return 0;
		else return scancode - SDL_SCANCODE_KP_1 + 1;
	}
	else return -1;
}

void Keyboard::sdl_init(){
#if defined(_WIN32) || defined(__linux__)
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("keyboard input, NEEDS TO BE IN FOCUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 200, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
#endif // _WIN32 || derfined __linux__
}

void Keyboard::check_for_keyboard_events() {
#if defined(_WIN32) || defined(__linux__)
	SDL_Event _event;
	while (1) {
		if (SDL_PollEvent(&_event)) {
			if (_event.type == SDL_QUIT) {
				break;
			}
			else if (_event.type == SDL_KEYDOWN) {
				_window_manager->handle_key_down(scancode_to_keycode(_event));
			}
			else if (_event.type == SDL_KEYUP) {
				_window_manager->handle_key_up(scancode_to_keycode(_event));
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_time));
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
#endif // _WIN32 || derfined __linux__
}

uint8_t Keyboard::scancode_to_keycode(SDL_Event _event) {
	if (is_key_down(SDL_SCANCODE_RSHIFT) || is_key_down(SDL_SCANCODE_LSHIFT)) {
		switch (_event.key.keysym.scancode) {
			//letters
		case 4: return keyMap.at("A");
		case 5: return keyMap.at("B");
		case 6: return keyMap.at("C");
		case 7: return keyMap.at("D");
		case 8: return keyMap.at("E");
		case 9: return keyMap.at("F");
		case 10: return keyMap.at("G");
		case 11: return keyMap.at("H");
		case 12: return keyMap.at("I");
		case 13: return keyMap.at("J");
		case 14: return keyMap.at("K");
		case 15: return keyMap.at("L");
		case 16: return keyMap.at("M");
		case 17: return keyMap.at("N");
		case 18: return keyMap.at("O");
		case 19: return keyMap.at("P");
		case 20: return keyMap.at("Q");
		case 21: return keyMap.at("R");
		case 22: return keyMap.at("S");
		case 23: return keyMap.at("T");
		case 24: return keyMap.at("U");
		case 25: return keyMap.at("V");
		case 26: return keyMap.at("W");
		case 27: return keyMap.at("X");
		case 28: return keyMap.at("Y");
		case 29: return keyMap.at("Z");
			// everything else
		case 84: return keyMap.at("fraction");
		case 36: return keyMap.at("fraction");
		case 48: return keyMap.at("*");
		case 37: return keyMap.at("(");
		case 38: return keyMap.at(")");
		}
	}
	else {
		switch (_event.key.keysym.scancode) {
			// Numbers
		case 30: return keyMap.at("1");
		case 31: return keyMap.at("2");
		case 32: return keyMap.at("3");
		case 33: return keyMap.at("4");
		case 34: return keyMap.at("5");
		case 35: return keyMap.at("6");
		case 36: return keyMap.at("7");
		case 37: return keyMap.at("8");
		case 38: return keyMap.at("9");
		case 39: return keyMap.at("0");
			// Keypad Numbers
		case 89: return keyMap.at("1");
		case 90: return keyMap.at("2");
		case 91: return keyMap.at("3");
		case 92: return keyMap.at("4");
		case 93: return keyMap.at("5");
		case 94: return keyMap.at("6");
		case 95: return keyMap.at("7");
		case 96: return keyMap.at("8");
		case 97: return keyMap.at("9");
		case 98: return keyMap.at("0");
			// Letters
		case 4: return keyMap.at("a");
		case 5: return keyMap.at("b");
		case 6: return keyMap.at("c");
		case 7: return keyMap.at("d");
		case 8: return keyMap.at("e");
		case 9: return keyMap.at("f");
		case 10: return keyMap.at("g");
		case 11: return keyMap.at("h");
		case 12: return keyMap.at("i");
		case 13: return keyMap.at("j");
		case 14: return keyMap.at("k");
		case 15: return keyMap.at("l");
		case 16: return keyMap.at("m");
		case 17: return keyMap.at("n");
		case 18: return keyMap.at("o");
		case 19: return keyMap.at("p");
		case 20: return keyMap.at("q");
		case 21: return keyMap.at("r");
		case 22: return keyMap.at("s");
		case 23: return keyMap.at("t");
		case 24: return keyMap.at("u");
		case 25: return keyMap.at("v");
		case 26: return keyMap.at("w");
		case 27: return keyMap.at("x");
		case 28: return keyMap.at("y");
		case 29: return keyMap.at("z");
			// everything else
		case 79: return keyMap.at("left");
		case 80: return keyMap.at("right");
		case 81: return keyMap.at("down");
		case 82: return keyMap.at("up");
		case 42: return keyMap.at("del");
		case 84: return keyMap.at("/");
		case 85: return keyMap.at("*");
		case 86: return keyMap.at("-");
		case 87: return keyMap.at("+");
		case 48: return keyMap.at("+");
		case 56: return keyMap.at("-");
			// default
		default: return keyMap.at("0");
		}
	}
}

void Keyboard::check_for_calc_button_presses() 
{
#if not defined(_WIN32) && not defined(__linux__)

	//TODO setup with pico
	//Pico button mapping to SDL keycodes

#endif // not _WIN32 && not defined __linux__
}

bool Keyboard::is_key_down(int scancode) {
#if defined(_WIN32) || defined(__linux__)
	return SDL_GetKeyboardState(NULL)[scancode];
#else
	return false;
#endif // _WIN32 || defined __linux__
}