#include "windows/CalculatorWindow.h"

CalculatorWindow::CalculatorWindow()
{
	calculated = false;
	equations = std::vector<Equation>(1);
	_equation_selected = &equations[0];

	//_variables = std::vector<Number>(9);
	//_equation_selected->set_variable_list(&_variables);
}

CalculatorWindow::~CalculatorWindow() {}

Bitset2D CalculatorWindow::update_window()
{
	if (_menu != Menu::None) {
		return _menu_rendered;
	}
	switch (_mode) {
	case Mode::COMP:
		clear_window();
		add_to_window(_equation_selected->get_rendered_equation(true), 0, 0);
		if (calculated) add_to_window(result_rendered, SCREEN_WIDTH - result_rendered.width(), SCREEN_HEIGHT - result_rendered.height());
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
				// else if (keypress.key_calculator == Chars::KEY_MAP.at("=")) {
				//	// TODO: output with , instead of .
				//	result = _equation_selected->calculate_equation(variables);
				//	if (Error::error_thrown()) {
				//		result_rendered = Error::render_error();
				//		Error::error_handled();
				//		calculated = true;
				//	} else {
				//		result_rendered = result.render();
				//		calculated = true;
				//	}
				//	// result_rendered = Graphics::create_text(std::to_string(result));
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
		if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) {
			_menu = Menu::None;
			calculated = false;
			_equation_selected->ac();
		} else if (keypress.key_calculator == Chars::KEY_MAP.at("right")) {
			_menu = Menu::None;
			calculated = false;
		} else if (keypress.key_calculator == Chars::KEY_MAP.at("left")) {
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
		if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) {
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
			break;
		case 4:
			_setup &= ~(1 << 2);
			_setup &= ~(1 << 3);
			break;
		case 5:
			_setup &= ~(1 << 2);
			_setup |= 1 << 3;
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
		if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) {
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
		_menu_rendered.set(0, 1, Graphics::create_text("1:Input", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text("2:Output", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("3:Deg", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("4:Rad", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 17, Graphics::create_text("5:Gra", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 17, Graphics::create_text("6:Fix", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 25, Graphics::create_text("7:Sci", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 25, Graphics::create_text("8:Norm", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_Pg2:
		_menu_rendered.set(0, 1, Graphics::create_text("1:ab/c", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text("2:d/c", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("3:STAT", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("4:PerD", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 17, Graphics::create_text("5:AbAut", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_Input:
	case Menu::Setup_Output:
		_menu_rendered.set(0, 1, Graphics::create_text("1:2D", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text("2:Linear", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_Fix:
		_menu_rendered.set(0, 1, Graphics::create_text("Fix 0~9", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_Sci:
		_menu_rendered.set(0, 1, Graphics::create_text("Sci 0~9", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_Norm:
		_menu_rendered.set(0, 1, Graphics::create_text("Norm 1~2", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_Stat:
		_menu_rendered.set(0, 1, Graphics::create_text("Häufigkeit?", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("1:EIN", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("2:AUS", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_PerD:
		_menu_rendered.set(0, 1, Graphics::create_text("Period. Darst?", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("1:EIN", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("2:AUS", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Setup_TurnOff:
		_menu_rendered.set(0, 1, Graphics::create_text("Abschaltautomat.", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("1:10 Min.", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("2:60 Min.", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Hyp:
		_menu_rendered.set(0, 1, Graphics::create_text("1:sinh", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text("2:cosh", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("3:tanh", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("4:sinh-1", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 17, Graphics::create_text("5:cosh-1", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 17, Graphics::create_text("6:tanh-1", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Verify:
		_menu_rendered.set(0, 1, Graphics::create_text("1:=", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text(std::vector<uint8_t>{ 2, 84, 178 }, Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("3:>", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("4:<", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 17, Graphics::create_text(std::vector<uint8_t>{ 5, 84, 176 }, Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 17, Graphics::create_text(std::vector<uint8_t>{ 6, 84, 177 }, Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Stat:
		// TODO
		break;
	case Menu::Dist:
		// TODO
		break;
	case Menu::Base:
		_menu_rendered.set(0, 1, Graphics::create_text("1:and", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text("2:or", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text("3:xor", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 9, Graphics::create_text("4:xnor", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 17, Graphics::create_text("5:not", Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 17, Graphics::create_text("6:neg", Graphics::SYMBOLS_6_HIGH), false);
		break;
	case Menu::Drg:
		_menu_rendered.set(0, 1, Graphics::create_text(std::vector<uint8_t>{ 1, 84, 187 }, Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(48, 1, Graphics::create_text(std::vector<uint8_t>{ 2, 84, 188 }, Graphics::SYMBOLS_6_HIGH), false);
		_menu_rendered.set(0, 9, Graphics::create_text(std::vector<uint8_t>{ 3, 84, 186 }, Graphics::SYMBOLS_6_HIGH), false);
		break;
	default:
		break;
	}
}