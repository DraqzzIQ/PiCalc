#include "Calculator.h"

Calculator::Calculator() {
	equation = Equation();
}

render_plane Calculator::update_window() {
	add_to_window(equation.renderEquation(), 5, 5);
	return get_render_canvas();
}

void Calculator::handle_keyboard_event(int key) {
	std::cout << key << "       ";
	switch (key) {
		case::SDL_SCANCODE_RIGHT:
			equation.moveCursor('r');
			return;
		case 48:
			equation.addValue('+');
			return;
		case 56:
			equation.addValue('-');
			return;
		case 85:
			equation.addValue('*');
			return;
		case 84:
			equation.addValue(FRACTION);
			return;
	}
	if (Keyboard::scancode_is_number(key))
	{
		equation.addValue('0' + Keyboard::scancode_to_number(key));
	}
}