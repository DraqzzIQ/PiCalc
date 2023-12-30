#include "windows/CalculatorWindow.h"

CalculatorWindow::CalculatorWindow()
{
	calculated = false;
	equations = std::vector<Equation>(1);
	_equation_selected = &equations[0];

	_variables = std::vector<Number*>(9);
	_equation_selected->set_variable_list(_variables);
}

CalculatorWindow::~CalculatorWindow() {}

Bitset2D CalculatorWindow::update_window()
{
	if (_menu != Menu::None) return _menu_rendered;

	switch (_mode) {
	case Mode::COMP:
		clear_window();
		add_to_window(_equation_selected->get_rendered_equation(), 0, 0);
		if (calculated) add_to_window(_result_rendered, SCREEN_WIDTH - _result_rendered.width(), SCREEN_HEIGHT - _result_rendered.height());
		return window;
	case Mode::STAT:
		add_to_window(Graphics::create_text("STAT"), 0, 0);
		return window;
	case Mode::TABLE:
		add_to_window(Graphics::create_text("TABLE"), 0, 0);
		return window;
	case Mode::DIST:
		add_to_window(Graphics::create_text("DIST"), 0, 0);
		return window;
	case Mode::VERIF:
		add_to_window(Graphics::create_text("VERIF"), 0, 0);
		return window;
	case Mode::BASE_N:
		add_to_window(Graphics::create_text("BASE_N"), 0, 0);
		return window;
	case Mode::EQ_SOLV:
		add_to_window(Graphics::create_text("EQ_SOLV"), 0, 0);
		return window;
	case Mode::GRAPH:
		add_to_window(Graphics::create_text("GRAPH"), 0, 0);
		return window;
	default:
		return window;
	}
}

void CalculatorWindow::handle_key_down(KeyPress keypress)
{
	switch (_menu) {
	case Menu::None:
		if (keypress.key_calculator == 129) set_menu(Menu::Setup_Pg1);
		else if (keypress.key_calculator == 105) set_menu(Menu::Mode);
		else {
			switch (_mode) {
			case Mode::COMP:
				if (keypress.key_calculator == Chars::KEY_MAP.at("right")) _equation_selected->move_cursor_right();
				else if (keypress.key_calculator == Chars::KEY_MAP.at("left")) _equation_selected->move_cursor_left();
				else if (keypress.key_calculator == Chars::KEY_MAP.at("up")) _equation_selected->move_cursor_up();
				else if (keypress.key_calculator == Chars::KEY_MAP.at("down")) _equation_selected->move_cursor_down();
				else if (keypress.key_calculator == Chars::KEY_MAP.at("DEL")) _equation_selected->del();
				else if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) _equation_selected->ac();
				else if (keypress.key_calculator == Chars::KEY_MAP.at("=")) {
					_result = _equation_selected->to_number();
					if (Error::error_thrown()) {
						set_menu(Menu::Error);
						Error::error_handled();
						calculated = false;
					} else {
						_result_equation = Equation(_result.to_key_set().at(0));
						_result_rendered = _result_equation.get_rendered_equation();
						calculated = true;
					}
				}
				// result_rendered = Graphics::create_text(std::to_string(result));
				else if (keypress.key_calculator == Chars::KEY_MAP.at("unknown"))
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
				else _equation_selected->add_value(keypress.key_calculator);
			}
		}
		break;
	case Menu::Error:
		if (keypress.key_calculator == 126) {
			_menu = Menu::None;
			calculated = false;
			_equation_selected->ac();
		} else if (keypress.key_calculator == 170) {
			_menu = Menu::None;
			calculated = false;
		} else if (keypress.key_calculator == 169) {
			_menu = Menu::None;
			calculated = false;
		}
		break;
	case Menu::Mode:
		switch (keypress.key_calculator) {
		case 1:
			_mode = Mode::COMP;
			set_menu(Menu::None);
			break;
		case 2:
			_mode = Mode::STAT;
			set_menu(Menu::Mode_Stat);
			break;
		case 3:
			_mode = Mode::TABLE;
			set_menu(Menu::None);
			break;
		case 4:
			_mode = Mode::DIST;
			set_menu(Menu::Mode_Dist);
			break;
		case 5:
			_mode = Mode::VERIF;
			set_menu(Menu::None);
			break;
		case 6:
			_mode = Mode::BASE_N;
			set_menu(Menu::None);
			break;
		case 7:
			_mode = Mode::EQ_SOLV;
			set_menu(Menu::None);
			break;
		case 8:
			_mode = Mode::GRAPH;
			set_menu(Menu::None);
			break;
		default:
			break;
		}
		break;
	case Menu::Mode_Stat:
		_mode = Mode::COMP;
		set_menu(Menu::None);
		calculated = false;
		// TODO
		break;
	case Menu::Mode_Dist:
		_mode = Mode::COMP;
		set_menu(Menu::None);
		calculated = false;
		// TODO
		break;
	case Menu::Setup_Pg1:
		if (keypress.key_calculator == 126) {
			set_menu(Menu::None);
			calculated = false;
		}
		switch (keypress.key_calculator) {
		case 1:
			set_menu(Menu::Setup_Input);
			break;
		case 2:
			set_menu(Menu::Setup_Output);
			break;
		case 3:
			_setup |= 1 << 2;
			_setup &= ~(1 << 3);
			_menu = Menu::None;
			break;
		case 4:
			_setup &= ~(1 << 2);
			_setup &= ~(1 << 3);
			_menu = Menu::None;
			break;
		case 5:
			_setup &= ~(1 << 2);
			_setup |= 1 << 3;
			_menu = Menu::None;
			break;
		case 6:
			set_menu(Menu::Setup_Fix);
			break;
		case 7:
			set_menu(Menu::Setup_Sci);
			break;
		case 8:
			set_menu(Menu::Setup_Norm);
			break;
		default:
			break;
		}
		break;
	case Menu::Setup_Pg2:
		if (keypress.key_calculator == 126) {
			set_menu(Menu::None);
			calculated = false;
		}
		switch (keypress.key_calculator) {
		case 1:
			_setup |= 1 << 13;
			break;
		case 2:
			_setup &= ~(1 << 13);
			break;
		case 3:
			set_menu(Menu::Setup_Stat);
			break;
		case 4:
			set_menu(Menu::Setup_PerD);
			break;
		case 5:
			set_menu(Menu::Setup_TurnOff);
			break;
		}
		break;
	}
}

void CalculatorWindow::set_menu(Menu menu)
{
	// TODO: change strings to keycode vectors
	_menu = menu;
	_menu_rendered = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	switch (menu) {
	case Menu::Error:
		_menu_rendered = Error::render_error();
		break;
	case Menu::Mode:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 241, 12, 24, 22, 25 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 242, 28, 29, 10, 29 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 243, 29, 10, 11, 21, 14 }, false);
		_menu_rendered.put_chars(48, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 244, 16, 27, 10, 25, 17 }, false);
		_menu_rendered.put_chars(1, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 245, 13, 18, 28, 29 }, false);
		_menu_rendered.put_chars(48, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 246, 31, 14, 27, 18, 15 }, false);
		_menu_rendered.put_chars(1, 24, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 247, 11, 10, 28, 14, 23 }, false);
		_menu_rendered.put_chars(48, 24, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 248, 28, 24, 21, 31, 14 }, false);
		break;
	case Menu::Mode_Stat:
		// TODO
		break;
	case Menu::Mode_Dist:
		// TODO
		break;
	case Menu::Setup_Pg1:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 241, 84, 18, 53, 55, 60, 59 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 242, 84, 24, 60, 59, 55, 60, 59 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 243, 84, 13, 44, 46 }, false);
		_menu_rendered.put_chars(48, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 244, 84, 27, 40, 43 }, false);
		_menu_rendered.put_chars(1, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 245, 84, 16, 57, 40 }, false);
		_menu_rendered.put_chars(48, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 246, 84, 15, 48, 63 }, false);
		_menu_rendered.put_chars(1, 24, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 247, 84, 28, 42, 48 }, false);
		_menu_rendered.put_chars(48, 24, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 248, 84, 23, 54, 57, 52 }, false);
		break;
	case Menu::Setup_Pg2:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 40, 41, 175, 42 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 43, 175, 42 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 3, 84, 28, 29, 10, 29 }, false);
		_menu_rendered.put_chars(48, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 4, 84, 25, 44, 57, 13 }, false);
		_menu_rendered.put_chars(1, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 5, 84, 10, 41, 10, 60, 59 }, false);
		break;
	case Menu::Setup_Input:
	case Menu::Setup_Output:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 2, 13 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 21, 48, 53, 44, 40, 57 }, false);
		break;
	case Menu::Setup_Fix:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 15, 48, 63, 80, 0, 180, 9 }, false);
		break;
	case Menu::Setup_Sci:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 28, 42, 48, 80, 0, 180, 9 }, false);
		break;
	case Menu::Setup_Norm:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 23, 54, 57, 52, 80, 1, 180, 2 }, false);
		break;
	case Menu::Setup_Stat:
		_menu_rendered.put_chars(0, 1, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 17, 66, 60, 45, 48, 46, 50, 44, 48, 59, 86 }, false);
		_menu_rendered.put_chars(0, 9, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 14, 18, 23 }, false);
		_menu_rendered.put_chars(48, 9, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 10, 30, 28 }, false);
		break;
	case Menu::Setup_PerD:
		_menu_rendered.put_chars(0, 1, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 25, 44, 57, 48, 54, 43, 81, 80, 13, 40, 57, 58, 59, 86 }, false);
		_menu_rendered.put_chars(0, 9, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 14, 18, 23 }, false);
		_menu_rendered.put_chars(48, 9, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 10, 30, 28 }, false);
		break;
	case Menu::Setup_TurnOff:
		_menu_rendered.put_chars(0, 1, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 10, 41, 58, 42, 47, 40, 51, 59, 40, 60, 59, 54, 52, 40, 59, 81 }, false);
		_menu_rendered.put_chars(0, 9, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 1, 0, 80, 22, 48, 53, 81 }, false);
		_menu_rendered.put_chars(48, 9, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 6, 0, 80, 22, 48, 53, 81 }, false);
		break;
	case Menu::Hyp:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 58, 48, 53, 47 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 42, 54, 58, 47 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 3, 84, 59, 40, 53, 47 }, false);
		_menu_rendered.put_chars(48, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 4, 84, 58, 48, 53, 47, 70, 1 }, false);
		_menu_rendered.put_chars(1, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 5, 84, 42, 54, 58, 47, 70, 1 }, false);
		_menu_rendered.put_chars(48, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 6, 84, 59, 40, 53, 47, 70, 1 }, false);
		break;
	case Menu::Verify:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 73 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 178 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 88 }, false);
		_menu_rendered.put_chars(48, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 89 }, false);
		_menu_rendered.put_chars(1, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 5, 84, 176 }, false);
		_menu_rendered.put_chars(48, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 6, 84, 177 }, false);
		break;
	case Menu::Stat:
		// TODO
		break;
	case Menu::Dist:
		// TODO
		break;
	case Menu::Base:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 40, 53, 43 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 54, 57 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 3, 84, 63, 54, 57 }, false);
		_menu_rendered.put_chars(48, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 4, 84, 63, 53, 54, 57 }, false);
		_menu_rendered.put_chars(1, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 5, 84, 53, 54, 59 }, false);
		_menu_rendered.put_chars(48, 16, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 6, 84, 53, 44, 46 }, false);
		break;
	case Menu::Drg:
		_menu_rendered.put_chars(1, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 1, 84, 187 }, false);
		_menu_rendered.put_chars(48, 0, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 2, 84, 188 }, false);
		_menu_rendered.put_chars(1, 8, Graphics::SYMBOLS_7_HIGH, KEY_SET{ 3, 84, 186 }, false);
		break;
	default:
		break;
	}
}