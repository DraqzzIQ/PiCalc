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
		case SDL_SCANCODE_A: return keyMap.at("A");
		case SDL_SCANCODE_B: return keyMap.at("B");
		case SDL_SCANCODE_C: return keyMap.at("C");
		case SDL_SCANCODE_D: return keyMap.at("D");
		case SDL_SCANCODE_E: return keyMap.at("E");
		case SDL_SCANCODE_F: return keyMap.at("F");
		case SDL_SCANCODE_G: return keyMap.at("G");
		case SDL_SCANCODE_H: return keyMap.at("H");
		case SDL_SCANCODE_I: return keyMap.at("I");
		case SDL_SCANCODE_J: return keyMap.at("J");
		case SDL_SCANCODE_K: return keyMap.at("K");
		case SDL_SCANCODE_L: return keyMap.at("L");
		case SDL_SCANCODE_M: return keyMap.at("M");
		case SDL_SCANCODE_N: return keyMap.at("N");
		case SDL_SCANCODE_O: return keyMap.at("O");
		case SDL_SCANCODE_P: return keyMap.at("P");
		case SDL_SCANCODE_Q: return keyMap.at("Q");
		case SDL_SCANCODE_R: return keyMap.at("R");
		case SDL_SCANCODE_S: return keyMap.at("S");
		case SDL_SCANCODE_T: return keyMap.at("T");
		case SDL_SCANCODE_U: return keyMap.at("U");
		case SDL_SCANCODE_V: return keyMap.at("V");
		case SDL_SCANCODE_W: return keyMap.at("W");
		case SDL_SCANCODE_X: return keyMap.at("X");
		case SDL_SCANCODE_Y: return keyMap.at("Y");
		case SDL_SCANCODE_Z: return keyMap.at("Z");
			// everything else
		case SDL_SCANCODE_7: return keyMap.at("fraction");
		case SDL_SCANCODE_KP_DIVIDE: return keyMap.at("fraction");
		case SDL_SCANCODE_8: return keyMap.at("(");
		case SDL_SCANCODE_9: return keyMap.at(")");
		case 48: return keyMap.at("*");
		}
	}
	else {
		switch (_event.key.keysym.scancode) {
			// Numbers
		case SDL_SCANCODE_1: return keyMap.at("1");
		case SDL_SCANCODE_2: return keyMap.at("2");
		case SDL_SCANCODE_3: return keyMap.at("3");
		case SDL_SCANCODE_4: return keyMap.at("4");
		case SDL_SCANCODE_5: return keyMap.at("5");
		case SDL_SCANCODE_6: return keyMap.at("6");
		case SDL_SCANCODE_7: return keyMap.at("7");
		case SDL_SCANCODE_8: return keyMap.at("8");
		case SDL_SCANCODE_9: return keyMap.at("9");
		case SDL_SCANCODE_0: return keyMap.at("0");
			// Keypad Numbers
		case SDL_SCANCODE_KP_1: return keyMap.at("1");
		case SDL_SCANCODE_KP_2: return keyMap.at("2");
		case SDL_SCANCODE_KP_3: return keyMap.at("3");
		case SDL_SCANCODE_KP_4: return keyMap.at("4");
		case SDL_SCANCODE_KP_5: return keyMap.at("5");
		case SDL_SCANCODE_KP_6: return keyMap.at("6");
		case SDL_SCANCODE_KP_7: return keyMap.at("7");
		case SDL_SCANCODE_KP_8: return keyMap.at("8");
		case SDL_SCANCODE_KP_9: return keyMap.at("9");
		case SDL_SCANCODE_KP_0: return keyMap.at("0");
			// Letters
		case SDL_SCANCODE_A: return keyMap.at("a");
		case SDL_SCANCODE_B: return keyMap.at("b");
		case SDL_SCANCODE_C: return keyMap.at("c");
		case SDL_SCANCODE_D: return keyMap.at("d");
		case SDL_SCANCODE_E: return keyMap.at("e");
		case SDL_SCANCODE_F: return keyMap.at("f");
		case SDL_SCANCODE_G: return keyMap.at("g");
		case SDL_SCANCODE_H: return keyMap.at("h");
		case SDL_SCANCODE_I: return keyMap.at("i");
		case SDL_SCANCODE_J: return keyMap.at("j");
		case SDL_SCANCODE_K: return keyMap.at("k");
		case SDL_SCANCODE_L: return keyMap.at("l");
		case SDL_SCANCODE_M: return keyMap.at("m");
		case SDL_SCANCODE_N: return keyMap.at("n");
		case SDL_SCANCODE_O: return keyMap.at("o");
		case SDL_SCANCODE_P: return keyMap.at("p");
		case SDL_SCANCODE_Q: return keyMap.at("q");
		case SDL_SCANCODE_R: return keyMap.at("r");
		case SDL_SCANCODE_S: return keyMap.at("s");
		case SDL_SCANCODE_T: return keyMap.at("t");
		case SDL_SCANCODE_U: return keyMap.at("u");
		case SDL_SCANCODE_V: return keyMap.at("v");
		case SDL_SCANCODE_W: return keyMap.at("w");
		case SDL_SCANCODE_X: return keyMap.at("x");
		case SDL_SCANCODE_Y: return keyMap.at("y");
		case SDL_SCANCODE_Z: return keyMap.at("z");
			// everything else
		case SDL_SCANCODE_LEFT: return keyMap.at("left");
		case SDL_SCANCODE_RIGHT: return keyMap.at("right");
		case SDL_SCANCODE_DOWN: return keyMap.at("down");
		case SDL_SCANCODE_UP: return keyMap.at("up");
		case SDL_SCANCODE_BACKSPACE: return keyMap.at("del");
		case SDL_SCANCODE_KP_DIVIDE: return keyMap.at("/");
		case SDL_SCANCODE_KP_MULTIPLY: return keyMap.at("*");
		case SDL_SCANCODE_KP_MINUS: return keyMap.at("-");
		case SDL_SCANCODE_KP_PLUS: return keyMap.at("+");
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