#include "Calculator.h"

Calculator::Calculator() {
	equation = new Equation();
}

render_plane Calculator::update_window() {
	clear_window();
	add_to_window(equation->render_equation(), 5, 5);
	return get_render_canvas();
}

void Calculator::handle_key_down(KeyPress keypress) {
	std::cout << keypress.key << "       ";
	
	if (keypress.key == Chars::KEY_MAP.at("right")) equation->move_cursor_right();
	else if (keypress.key == Chars::KEY_MAP.at("left")) equation->move_cursor_left();
	else if (keypress.key == Chars::KEY_MAP.at("del")) equation->del();
	else equation->add_value(keypress.key);
}