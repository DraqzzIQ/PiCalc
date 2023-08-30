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
	if (keypress.key_calculator == Chars::KEY_MAP.at("right")) equation->move_cursor_right();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("left")) equation->move_cursor_left();
	//else if (keypress.key_calculator == Chars::KEY_MAP.at("up")) equation->move_cursor_up();
	//else if (keypress.key_calculator == Chars::KEY_MAP.at("down")) equation->move_cursor_down();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("DEL")) equation->del();
	//else if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) equation->ac();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("=")) equation->calculate_equation();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("unknown"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("SHIFT"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("ALPHA"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("MODE"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("SETUP"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("STO"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("RCL"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("CONST"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("STAT/DIST"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at(":"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("FACT"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("ENG"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("<-"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("CONV"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("Conv"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("hyp"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("CLR"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("VERIFY"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("BASE"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("INS"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("DRG"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("M+"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("M-"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("OFF"));
	else if (keypress.key_calculator == Chars::KEY_MAP.at("wav="));
	else equation->add_value(keypress.key_calculator);
}