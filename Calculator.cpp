#include "Calculator.h"

Calculator::Calculator() {
	equation = Equation();
}

render_plane Calculator::update_window() {
	add_to_window(equation.renderEquation(), 5, 5);
	return get_render_canvas();
}

void Calculator::handle_keyboard_event(int key, bool shift) {
	std::cout << key << "       ";
	if (shift) {
		switch (key) {
		case 84:
			equation.addValue(FRACTION);
			return;
		case SDL_SCANCODE_7:
			equation.addValue(FRACTION);
			return;
		case 48:
			equation.addValue('*');
			return;
		case SDL_SCANCODE_8:
			equation.addValue('(');
			return;
		case SDL_SCANCODE_9:
			equation.addValue(')');
			return;
		}
	}
	else {
		switch (key) {
		case SDL_SCANCODE_RIGHT:
			equation.moveCursor('r');
			return;
		case 84:
			equation.addValue('/');
			return;
		case 85:
			equation.addValue('*');
			return;
		case 86:
			equation.addValue('-');
			return;
		case 87:
			equation.addValue('+');
			return;

		case 48:
			equation.addValue('+');
			return;
		case 56:
			equation.addValue('-');
			return;
		}
	}
	int number = Keyboard::scancode_to_number(key);
	if (number != -1)
	{
		equation.addValue('0' + Keyboard::scancode_to_number(key));
		return;
	}
}