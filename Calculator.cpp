#include "Calculator.h"

Calculator::Calculator() {
	equation = Equation();
}

render_plane Calculator::update_window() {
	add_to_window(equation.renderEquation(), 5, 5);
	return get_render_canvas();
}

void Calculator::handle_keyboard_event(int key) {
	//std::cout << key;
	switch (key) {
		case::SDL_SCANCODE_RIGHT:
			equation.moveCursor('r');
		case::SDL_SCANCODE_BACKSLASH:
			equation.addValue(FRACTION);
		case::SDL_SCANCODE_0:
			equation.addValue('0');
		case::SDL_SCANCODE_1:
			equation.addValue('1');
	}
	/*if (Keyboard::scancode_is_number(key))
	{
		int number = Keyboard::scancode_to_number(key);
		std::cout << static_cast<char>(number);
		equation.addValue(static_cast<char>(number));
	}*/
}