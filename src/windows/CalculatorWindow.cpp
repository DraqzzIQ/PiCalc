#include "windows/CalculatorWindow.h"

CalculatorWindow::CalculatorWindow()
{
	equation = new Equation();
	result = 0;
	calculated = false;
}

CalculatorWindow::~CalculatorWindow()
{
	delete equation;
}

Bitset2D CalculatorWindow::update_window()
{
	clear_window();
	add_to_window(equation->get_rendered_equation(), 0, 1);
	if (calculated) add_to_window(result_rendered, SCREEN_WIDTH - result_rendered.width(), SCREEN_HEIGHT - result_rendered.height());
	return get_render_canvas();
}


void CalculatorWindow::handle_key_down(KeyPress keypress)
{
	Equation::Error error;
	if (keypress.key_calculator == Chars::KEY_MAP.at("right")) equation->move_cursor_right();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("left")) equation->move_cursor_left();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("up")) equation->move_cursor_up();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("down")) equation->move_cursor_down();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("DEL")) equation->del();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) equation->ac();
	else if (keypress.key_calculator == Chars::KEY_MAP.at("=")) {
		result = equation->calculate_equation(variables, error);
		result_rendered = Graphics::create_text(std::to_string(result));
		calculated = true;
	} else if (keypress.key_calculator == Chars::KEY_MAP.at("unknown"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("SHIFT"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("ALPHA"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("MODE"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("SETUP"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("STO"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("RCL"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("CONST"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("STAT/DIST"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at(":"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("FACT"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("ENG"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("<-"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("CONV"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("Conv"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("hyp"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("CLR"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("VERIFY"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("BASE"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("INS"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("DRG"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("M+"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("M-"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("OFF"))
		;
	else if (keypress.key_calculator == Chars::KEY_MAP.at("wav="))
		;
	else equation->add_value(keypress.key_calculator);
}
