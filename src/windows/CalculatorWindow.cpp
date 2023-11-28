#include "windows/CalculatorWindow.h"

CalculatorWindow::CalculatorWindow()
{
	result = 0;
	calculated = false;
}

CalculatorWindow::~CalculatorWindow()
{
}

Bitset2D CalculatorWindow::update_window()
{
	clear_window();
	add_to_window(equation.get_rendered_equation(), 0, 1);
	if (calculated) add_to_window(result_rendered, SCREEN_WIDTH - result_rendered.width(), SCREEN_HEIGHT - result_rendered.height());
	return get_render_canvas();
}


bool CalculatorWindow::handle_key_down(KeyPress keypress)
{
	Equation::Error error;
	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("right")) equation.move_cursor_right();
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("left")) equation.move_cursor_left();
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("up")) equation.move_cursor_up();
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("down")) equation.move_cursor_down();
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("DEL")) equation.del();
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("AC")) equation.ac();
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("=")) {
		// TODO: output with , instead of .
		result = equation.calculate_equation(variables, error);
		// result_rendered = Graphics::create_text(std::to_string(result));
		result_rendered = result.render();
		calculated = true;
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("unknown"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("SHIFT"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("ALPHA"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("MODE"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("SETUP"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("STO"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("RCL"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("CONST"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("STAT/DIST"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at(":"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("FACT"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("ENG"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("<-"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("CONV"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("Conv"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("hyp"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("CLR"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("VERIFY"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("BASE"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("INS"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("DRG"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("M+"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("M-"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("OFF"))
		;
	else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("wav="))
		;
	else equation.add_value(keypress.key_calculator);

	return true;
}