#include "Calculator.h"

Calculator::Calculator() {
	equation = Equation();
}

render_plane Calculator::update_window() {
	clear_window();
	add_to_window(equation.renderEquation(), 5, 5);
	return get_render_canvas();
}

void Calculator::handle_key_down(int key) {
	std::cout << key << "       ";
	if (Keyboard::is_key_down(SDL_SCANCODE_RSHIFT) || Keyboard::is_key_down(SDL_SCANCODE_LSHIFT)) {
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
		case SDL_SCANCODE_LEFT:
			equation.moveCursor('l');
			return;
		case SDL_SCANCODE_BACKSPACE:
			equation.del();
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