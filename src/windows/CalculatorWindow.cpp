#include "windows/CalculatorWindow.h"

CalculatorWindow::CalculatorWindow()
{
	calculated = false;
	equations = std::vector<Equation>(1);
	_equation_selected = &equations[0];

	_variables = std::vector<Number*>(9);
	_equation_selected->set_variable_list(_variables);
	_result_selected = 0;

	_result_equation.set_cursor_state(false);
}

CalculatorWindow::~CalculatorWindow() {}

void CalculatorWindow::update_window()
{
	if (_menu != Menu::None) return;

	switch (_mode) {
	case Mode::COMP:
		clear_window();
		_window.set(0, 1, _equation_selected->get_rendered_equation(), false);
		if (calculated) _window.set(SCREEN_WIDTH - _result_rendered.width(), SCREEN_HEIGHT - _result_rendered.height() + 1, _result_rendered, false);
		return;
	case Mode::STAT:
		return;
	case Mode::TABLE:
		return;
	case Mode::DIST:
		return;
	case Mode::VERIF:
		return;
	case Mode::BASE_N:
		return;
	case Mode::EQ_SOLV:
		return;
	case Mode::GRAPH:
		return;
	default:
		return;
	}
}

bool CalculatorWindow::handle_key_down(KeyPress keypress)
{
	switch (_menu) {
	case Menu::None:
		if (keypress.key_calculator == 8) set_menu(Menu::Setup_Pg1);
		else if (keypress.key_calculator == 7) set_menu(Menu::Mode);
		else {
			switch (_mode) {
			case Mode::COMP:
				switch (keypress.key_calculator) {
				case 3: _equation_selected->move_cursor_up(); break;
				case 4: _equation_selected->move_cursor_down(); break;
				case 5: _equation_selected->move_cursor_left(); break;
				case 6: _equation_selected->move_cursor_right(); break;
				case 153: _equation_selected->del(); break;
				case 155: _equation_selected->ac(); break;
				case '=':
					// ERROR: 3(1/4), 3*(1/4)
					_result = _equation_selected->to_number(_setup);
					if (Error::error_thrown()) {
						set_menu(Menu::Error);
						Error::error_handled();
						calculated = false;
					} else {
						_result_selected = 0;
						_result_key_sets = _result.get_all_representations(_variables);
						_result_equation.set_key_set(_result_key_sets.at(0));
						_result_rendered = _result_equation.get_rendered_equation();
						calculated = true;
					}
					break;
				case 0: break; // unknown
				case 1: break; // SHIFT
				case 2: break; // ALPHA
				case 145:      // S<>D
					if (!calculated) break;
					_result_selected++;
					if (_result_selected == _result_key_sets.size()) _result_selected = 0;
					_result_equation.set_key_set(_result_key_sets.at(_result_selected));
					_result_rendered = _result_equation.get_rendered_equation();
					break;
				case 142: break; // STO
				case 141: break; // RCL
				case 149: break; // CONST
				case 162: break; // STAT/DIST
				case ':': break;
				case 30: break;  // FACT
				case 143: break; // ENG
				case 144: break; // <-
				case 150: break; // SHIFT_CONV
				case 151: break; // ALPHA_CONV
				case 31: break;  // hyp
				case 152: break; // CLR
				case 157: break; // VERIFY
				case 163: break; // BASE
				case 154: break; // INS
				case 179: break; // DRG
				case 147: break; // M+
				case 148: break; // M-
				case 180: break; // wav=
				default: _equation_selected->add_value(keypress.key_calculator);
				}
			}
		}
		break;
	case Menu::Error:
		if (keypress.key_calculator == 155) {
			_menu = Menu::None;
			calculated = false;
			_equation_selected->ac();
		} else if (keypress.key_calculator == 5 || keypress.key_calculator == 6) {
			_menu = Menu::None;
			calculated = false;
		}
		break;
	case Menu::Mode:
		switch (keypress.key_calculator) {
		case '1':
			_mode = Mode::COMP;
			set_menu(Menu::None);
			break;
		case '2':
			_mode = Mode::STAT;
			set_menu(Menu::Mode_Stat);
			break;
		case '3':
			_mode = Mode::TABLE;
			set_menu(Menu::None);
			break;
		case '4':
			_mode = Mode::DIST;
			set_menu(Menu::Mode_Dist);
			break;
		case '5':
			_mode = Mode::VERIF;
			set_menu(Menu::None);
			break;
		case '6':
			_mode = Mode::BASE_N;
			set_menu(Menu::None);
			break;
		case '7':
			_mode = Mode::EQ_SOLV;
			set_menu(Menu::None);
			break;
		case '8':
			_mode = Mode::GRAPH;
			set_menu(Menu::None);
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
		if (keypress.key_calculator == 155) {
			set_menu(Menu::None);
			calculated = false;
		}
		switch (keypress.key_calculator) {
		case '1':
			set_menu(Menu::Setup_Input);
			break;
		case '2':
			set_menu(Menu::Setup_Output);
			break;
		case '3':
			_setup |= 1 << 2;
			_setup &= ~(1 << 3);
			_menu = Menu::None;
			break;
		case '4':
			_setup &= ~(1 << 2);
			_setup &= ~(1 << 3);
			_menu = Menu::None;
			break;
		case '5':
			_setup &= ~(1 << 2);
			_setup |= 1 << 3;
			_menu = Menu::None;
			break;
		case '6':
			set_menu(Menu::Setup_Fix);
			break;
		case '7':
			set_menu(Menu::Setup_Sci);
			break;
		case '8':
			set_menu(Menu::Setup_Norm);
			break;
		}
		break;
	case Menu::Setup_Pg2:
		if (keypress.key_calculator == 155) {
			set_menu(Menu::None);
			calculated = false;
		}
		switch (keypress.key_calculator) {
		case '1':
			_setup |= 1 << 13;
			break;
		case '2':
			_setup &= ~(1 << 13);
			break;
		case '3':
			set_menu(Menu::Setup_Stat);
			break;
		case '4':
			set_menu(Menu::Setup_PerD);
			break;
		}
		break;
	}
	return true;
}

void CalculatorWindow::set_menu(Menu menu)
{
	// TODO: change strings to keycode vectors
	_menu = menu;
	clear_window();
	switch (menu) {
	case Menu::Error:
		_window = Error::render_error();
		break;
	case Menu::Mode:
		_window.put_chars(1, 1, Graphics::SYMBOLS_7_HIGH, "\306COMP", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_7_HIGH, "\307STAT", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_7_HIGH, "\310TABLE", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_7_HIGH, "\311DIST", false);
		_window.put_chars(1, 17, Graphics::SYMBOLS_7_HIGH, "\312VERIF", false);
		_window.put_chars(48, 17, Graphics::SYMBOLS_7_HIGH, "\313BASE-N", false);
		_window.put_chars(1, 25, Graphics::SYMBOLS_7_HIGH, "\314EQ-SLV", false);
		_window.put_chars(48, 25, Graphics::SYMBOLS_7_HIGH, "\315GRAPH", false);
		break;
	case Menu::Mode_Stat:
		// TODO
		break;
	case Menu::Mode_Dist:
		// TODO
		break;
	case Menu::Setup_Pg1:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:Input", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:Output", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_6_HIGH, "3:Deg", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "4:Rad", false);
		_window.put_chars(1, 17, Graphics::SYMBOLS_6_HIGH, "5:Gra", false);
		_window.put_chars(48, 17, Graphics::SYMBOLS_6_HIGH, "6:Fix", false);
		_window.put_chars(1, 25, Graphics::SYMBOLS_6_HIGH, "7:Sci", false);
		_window.put_chars(48, 25, Graphics::SYMBOLS_6_HIGH, "8:Norm", false);
		break;
	case Menu::Setup_Pg2:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:ab/c", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:d/c", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_6_HIGH, "3:STAT", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "4:PerD", false);
		break;
	case Menu::Setup_Input:
	case Menu::Setup_Output:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:Mth2D", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:Linear", false);
		break;
	case Menu::Setup_Fix:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Fix 0~9", false);
		break;
	case Menu::Setup_Sci:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Sci 0~9", false);
		break;
	case Menu::Setup_Norm:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Norm 1~2", false);
		break;
	case Menu::Setup_Stat:
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Häufigkeit?", false);
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "1:EIN", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "2:AUS", false);
		break;
	case Menu::Setup_PerD:
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Period. Darst.?", false);
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "1:EIN", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "2:AUS", false);
		break;
	case Menu::Hyp:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:sinh", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:cosh", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_6_HIGH, "3:tanh", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "4:sinh\16", false);
		_window.put_chars(1, 17, Graphics::SYMBOLS_6_HIGH, "5:cosh\16", false);
		_window.put_chars(48, 17, Graphics::SYMBOLS_6_HIGH, "6:tanh\16", false);
		break;
	case Menu::Verify:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:=", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:\266", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_6_HIGH, "3:>", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "4:<", false);
		_window.put_chars(1, 17, Graphics::SYMBOLS_6_HIGH, "5:\267", false);
		_window.put_chars(48, 17, Graphics::SYMBOLS_6_HIGH, "6:\270", false);
		break;
	case Menu::Stat:
		// TODO
		break;
	case Menu::Dist:
		// TODO
		break;
	case Menu::Base:
		// TODO: Page 2
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:and", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:or", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_6_HIGH, "3:xor", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "4:xnor", false);
		_window.put_chars(1, 17, Graphics::SYMBOLS_6_HIGH, "5:Not", false);
		_window.put_chars(48, 17, Graphics::SYMBOLS_6_HIGH, "6:Neg", false);
		break;
	case Menu::Drg:
		_window.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "1:°", false);
		_window.put_chars(48, 1, Graphics::SYMBOLS_6_HIGH, "2:\256", false);
		_window.put_chars(1, 9, Graphics::SYMBOLS_6_HIGH, "3:\257", false);
		break;
	default:
		break;
	}
}