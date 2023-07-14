#include "Keyboard.h"

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
			if (_event.type == SDL_KEYDOWN) {
				_window_manager->handle_key_down(_event.key.keysym.scancode);
			}
			if (_event.type == SDL_KEYUP) {
				_window_manager->handle_key_up(_event.key.keysym.scancode);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_time));
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
#endif // _WIN32 || derfined __linux__
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