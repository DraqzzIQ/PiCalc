#include "Calculator.h"

Calculator::Calculator() {
	equation = Equation();
}

render_plane Calculator::update_window() {
	clear_window();
	add_to_window(equation.renderEquation(), 5, 5);
	return get_render_canvas();
}

void Calculator::handle_key_down(uint8_t key) {
	std::cout << key << "       ";
	
	if (key == keyMap.at("right")) equation.moveCursorRight();
	else if (key == keyMap.at("left")) equation.moveCursorLeft();
	else if (key == keyMap.at("del")) equation.del();
	else equation.addValue(key);
}