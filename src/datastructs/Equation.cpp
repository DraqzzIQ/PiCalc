#include "Equation.h"

// TODO: TIME, Font aligned bottom
const KEY_SET Equation::_allowed_calculate_operations = { KEY_MOD, '+', '-', KEY_PLUS_MINUS, KEY_MULTIPLY, KEY_DIVIDE };
const KEY_SET Equation::_bracket_keys = { KEY_LOG, KEY_LN, '(', KEY_SIN, KEY_COS, KEY_TAN, KEY_ASIN, KEY_ACOS, KEY_ATAN, KEY_SINH, KEY_COSH, KEY_TANH, KEY_ASINH, KEY_ACOSH, KEY_ATANH, KEY_GCD, KEY_LCM, KEY_POL, KEY_INT, KEY_REC, KEY_INTG, KEY_RND, KEY_RAN_INT };
const KEY_SET Equation::_values_before_exponent = { ')', '!', KEY_TIME, KEY_SCIENTIFIC_E, KEY_ANS, KEY_RAN, KEY_PI, KEY_EULER, KEY_RADIAN, KEY_GRADIAN, KEY_DEGREE };
const KEY_SET Equation::_symbols = { KEY_ABS, KEY_LOGN, KEY_FRACTION, KEY_MIXED_FRACTION, KEY_SQRT, KEY_PERIODIC, KEY_POWER, KEY_ROOTN, KEY_POWER10, KEY_EXP };
const std::map<KEY, std::string> Equation::_bracket_keys_text{
	{ KEY_LOG, "log" },
	{ KEY_LN, "ln" },
	{ '(', "(" },
	{ KEY_SIN, "sin" },
	{ KEY_COS, "cos" },
	{ KEY_TAN, "tan" },
	{ KEY_ASIN, "sin" },
	{ KEY_ACOS, "cos\16" },
	{ KEY_ATAN, "tan\16" },
	{ KEY_SINH, "sinh\16" },
	{ KEY_COSH, "cosh" },
	{ KEY_TANH, "tanh" },
	{ KEY_ASINH, "sinh\16" },
	{ KEY_ACOSH, "cosh\16" },
	{ KEY_ATANH, "tanh\16" },
	{ KEY_GCD, "GCD" },
	{ KEY_LCM, "LCM" },
	{ KEY_POL, "Pol" },
	{ KEY_INT, "Int" },
	{ KEY_REC, "Rec" },
	{ KEY_INTG, "Intg" },
	{ KEY_RND, "Rnd" },
	{ KEY_RAN_INT, "RanInt#" }
};
const std::map<KEY, std::string> Equation::_symbols_text{
	{ KEY_ABS, "abs(" },
	{ KEY_LOGN, "log(" },
	{ KEY_FRACTION, "((" },
	{ KEY_MIXED_FRACTION, "(" },
	{ KEY_SQRT, "sqrt(" },
	{ KEY_PERIODIC, "periodic" },
	{ KEY_POWER, "^(" },
	{ KEY_ROOTN, "root(" },
	{ KEY_POWER10, "10^(" },
	{ KEY_EXP, "exp(" }
};

Equation::Equation()
{
	_equation = KEY_SET(0);
	_cursor_index = 0;
	render_equation();
}

Equation::Equation(const KEY_SET& equation)
{
	_equation = equation;
	_cursor_index = 0;
	render_equation();
}

Equation::~Equation()
{
}


void Equation::set_frame_size(uint32_t width, uint32_t height)
{
	_frame_width = width;
	_frame_height = height;
}

void Equation::set_cursor_state(bool active)
{
	_cursor_active = active;
}

void Equation::set_key_set(const KEY_SET& equation)
{
	_equation = equation;
	_cursor_index = 0;
	render_equation();
}

Bitset2D Equation::get_rendered_equation(bool complete)
{
	// change _show_cursor every 500ms if cursor is active
	// TODO: fix dumb error of _last_blink_time not being 0
	// std::cout << _last_blink_time << " " << Utils::us_since_boot() << std::endl;
	if (!_cursor_active) _show_cursor = false;
	else if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time = Utils::us_since_boot();
		_show_cursor = !_show_cursor;
	}

	if (complete) return _show_cursor ? _rendered_equation_cursor : _rendered_equation;
	else return _show_cursor ? _rendered_equation_cursor_frame : _rendered_equation_frame;
}

const KEY_SET* Equation::get_raw_bytes() const
{
	return &_equation;
}

std::string Equation::get_ascii_bytes(bool english) const
{
	// TODO: check if works
	std::string result;
	result.reserve(_equation.size());
	std::vector<KEY> current_symbols;
	for (KEY key : _equation) {
		if (Utils::in_key_set(key, _symbols)) {
			for (KEY symbol : _symbols_text.at(key)) result.push_back(symbol);
		} else if (Utils::in_key_set(key, _bracket_keys)) {
			for (KEY symbol : _bracket_keys_text.at(key)) result.push_back(symbol);
			result.push_back('(');
		} else if (key == KEY_MOD) result.append(" mod ");
		else if (Utils::in_key_set(key, _allowed_calculate_operations)) {
			result.push_back(' ');
			result.push_back(key);
			result.push_back(' ');
		} else if (key == KEY_NEXT_VAL) {
			if (current_symbols.back() == KEY_MIXED_FRACTION) {
				result.append(" + (");
				current_symbols.back() = KEY_FRACTION;
			} else if (current_symbols.back() == KEY_FRACTION) result.append(") / (");
			else result.append(", ");
		} else if (key == KEY_SYMBOL_END) {
			if (current_symbols.back() == KEY_FRACTION) result.push_back(')');
			if (current_symbols.back() != KEY_PERIODIC) result.push_back(')');
		} else if (key == ',') {
			if (english) result.push_back('.');
			else result.push_back(';');
			result.push_back(' ');
		} else if (key == ';') {
			if (english) result.push_back(',');
			else result.push_back(';');
			result.push_back(' ');
		} else result.push_back(key);
	}
	return result;
}


void Equation::del()
{
	if (_cursor_index == 0) return;
	KEY val = _equation.at(--_cursor_index);
	if (Utils::in_key_set(val, _symbols)) {
		_equation.erase(_equation.begin() + _cursor_index);
		uint8_t depth = 0;
		while (_cursor_index < _equation.size()) {
			val = _equation.at(_cursor_index);
			if (val == KEY_NEXT_VAL && depth == 0) {
				_equation.erase(_equation.begin() + _cursor_index);
				continue;
			} else if (val == KEY_SYMBOL_END) {
				if (depth == 0) {
					_equation.erase(_equation.begin() + _cursor_index);
					break;
				}
				depth--;
			} else if (Utils::in_key_set(val, _symbols)) depth++;
			_cursor_index++;
		}
	} else if (val != KEY_NEXT_VAL && val != KEY_SYMBOL_END) {
		_equation.erase(_equation.begin() + _cursor_index);
	}
	render_equation();
}

void Equation::ac()
{
	_equation = KEY_SET(0);
	_cursor_index = 0;
	render_equation();
}

void Equation::move_cursor_left()
{
	if (_cursor_index == 0) _cursor_index = _equation.size();
	else _cursor_index--;
	render_equation();
}

void Equation::move_cursor_right()
{
	if (_cursor_index == _equation.size()) _cursor_index = 0;
	else _cursor_index++;
	render_equation();
}

void Equation::move_cursor_up()
{
	// improve
	if (_cursor_index == 0) return;
	for (uint32_t i = _cursor_index - 1; i > 0; i--) {
		if (_equation.at(i) == KEY_NEXT_VAL) {
			_cursor_index = i;
			render_equation();
			return;
		} else if (_equation.at(i) == '\n') {
			uint32_t new_line_index = i;
			while (i != 0 && _equation.at(i - 1) != '\n') i--;
			_cursor_index -= new_line_index;
			_cursor_index--;
			if (i + _cursor_index > new_line_index) _cursor_index = new_line_index;
			else _cursor_index += i;
			render_equation();
			return;
		}
	}
}

void Equation::move_cursor_down()
{
	// improve
	for (uint32_t i = _cursor_index; i < _equation.size(); i++) {
		if (_equation.at(i) == KEY_NEXT_VAL) {
			_cursor_index = i + 1;
			render_equation();
			return;
		} else if (_equation.at(i) == '\n') {
			uint32_t new_line_index = i;
			i++;
			while (i < _equation.size() && _equation.at(i) != '\n') i++;
			uint32_t new_line_end = i;
			i = _cursor_index;
			while (i != 0 && _equation.at(i - 1) != '\n') i--;
			_cursor_index -= i;
			_cursor_index++;
			if (new_line_index + _cursor_index > new_line_end) _cursor_index = new_line_end;
			else _cursor_index += new_line_index;
			render_equation();
			return;
		}
	}
}

void Equation::handle_key_down(KEY keypress)
{
	switch (keypress) {
	case KEY_UP: move_cursor_up(); break;
	case KEY_DOWN: move_cursor_down(); break;
	case KEY_LEFT: move_cursor_left(); break;
	case KEY_RIGHT: move_cursor_right(); break;
	case KEY_DEL: del(); break;
	case KEY_AC: ac(); break;
	case KEY_ABS: add_value_raw(KEY_ABS, 0); break;
	case KEY_CUBED: add_value_raw(KEY_POWER, 2, KEY_SET{ '3' }); break;
	case KEY_RECIPROCAL: add_value_raw(KEY_POWER, 2, KEY_SET{ KEY_NEGATE, '1' }); break;
	case KEY_LOGN: add_value_raw(KEY_LOGN, 3); break;
	case KEY_FRACTION: add_value_raw(KEY_FRACTION, 4); break;
	case KEY_SQRT: add_value_raw(KEY_SQRT, 1); break;
	case KEY_SQUARED: add_value_raw(KEY_POWER, 2, KEY_SET{ '2' }); break;
	case KEY_POWER: add_value_raw(KEY_POWER, 1); break;
	case KEY_MIXED_FRACTION: add_value_raw(KEY_MIXED_FRACTION, 6); break;
	case KEY_ROOT3: add_value_raw(KEY_ROOTN, 5, KEY_SET{ '3' }); break;
	case KEY_PERIODIC: add_value_raw(KEY_PERIODIC, 1); break;
	case KEY_ROOTN: add_value_raw(KEY_ROOTN, 4); break;
	case KEY_POWER10: add_value_raw(KEY_POWER10, 1); break;
	case KEY_EXP: add_value_raw(KEY_EXP, 1); break;
	default: _equation.insert(_equation.begin() + _cursor_index++, keypress); break;
	}
	render_equation();
}


void Equation::set_variable_list(std::map<KEY, Number*>* variables)
{
	_variables = variables;
}

Number* Equation::to_number(uint16_t settings)
{
	_settings = settings;
	_calculate_index = 0;
	Number* res = to_number_part(0);
	render_equation();
	return res;
}


void Equation::render_equation()
{
	// show the cursor and reset the blink timer
	_last_blink_time = Utils::us_since_boot();
	_show_cursor = true;

	// print the equation below the screen to the console for debugging
	// std::cout << to_string_simple();

	// render the equation without the cursor
	_render_index = 0;
	_cursor_data = { 0, 0, 0 };
	int32_t y_origin = 0;
	bool cursor_in_equation = false;
	_rendered_equation = render_equation_part(9, y_origin, cursor_in_equation, 0, 0, 1, 0);
	_rendered_equation.extend_right(1, false);

	// add the cursor to the equation
	_rendered_equation_cursor = _rendered_equation;
	_rendered_equation_cursor.set(_cursor_data.x, _cursor_data.y, Bitset2D(2, _cursor_data.size, true), false);

	// recalculate frame position
	// TODO: show as much as possible
	if (_cursor_data.x < _frame_x + 3) _frame_x = _cursor_data.x < 3 ? 0 : _cursor_data.x - 3;
	else if (_cursor_data.x > _frame_x + _frame_width - 4) _frame_x = _cursor_data.x - _frame_width + 4;
	if (_cursor_data.y < _frame_y + 3) _frame_y = _cursor_data.y < 3 ? 0 : _cursor_data.y - 3;
	else if (_cursor_data.y + _cursor_data.size > _frame_y + _frame_height - 2) _frame_y = _cursor_data.y - _frame_height + 2 + _cursor_data.size;

	// get a part of the rendered equation with width frame_width and height frame_height
	_rendered_equation.copy(_frame_x, _frame_y, _frame_width, _frame_height, _rendered_equation_frame);
	_rendered_equation_cursor.copy(_frame_x, _frame_y, _frame_width, _frame_height, _rendered_equation_cursor_frame);
}

Bitset2D Equation::render_equation_part(uint8_t font_height, int32_t& y_origin, bool& cursor_inside_ref, int32_t cursor_offset_x, int32_t cursor_offset_y, uint8_t cursor_alignment, uint8_t type)
{
	// TODO: smaller Fonts
	FONT* table = nullptr;
	if (font_height < 5) font_height = 5;
	else if (font_height > 9) font_height = 9;

	switch (font_height) {
	case 5: table = &Graphics::SYMBOLS_5_HIGH; break;
	case 6: table = &Graphics::SYMBOLS_6_HIGH; break;
	case 7: table = &Graphics::SYMBOLS_7_HIGH; break;
	case 8: table = &Graphics::SYMBOLS_7_HIGH; break;
	case 9: table = &Graphics::SYMBOLS_9_HIGH; break;
	}

	Bitset2D equation_part(1, font_height, false);
	bool cursor_inside = false;
	y_origin = 0;
	if (type == 1) _render_index++;

	KEY last_rendered = 0;

	for (; _render_index < _equation.size(); _render_index++) {
		KEY value = _equation.at(_render_index);

		Bitset2D symbol_matrix;

		if (_render_index == _cursor_index) {
			_cursor_data = { equation_part.width() - 1, 0, font_height };
			cursor_inside = true;
		}

		// any symbol with an open bracket at the end
		if (Utils::in_key_set(value, _bracket_keys) && value != '(') {
			// only render the text before the bracket, then change the value to 40 for the other case to render the actual bracket
			std::string keys = _bracket_keys_text.at(value);
			for (uint8_t j = 0; j < keys.size(); j++) {
				symbol_matrix.extend_right(table->at(keys.at(j)));
				symbol_matrix.extend_right(1, false);
			}
			symbol_matrix.extend_up(y_origin, false);
			symbol_matrix.extend_down(equation_part.height() - symbol_matrix.height(), false);
			equation_part.extend_right(symbol_matrix);
			value = '(';
		}

		// open bracket
		if (value == '(') {
			// render everything until the closing bracket
			int32_t new_y_origin = 0;
			_render_index++;
			symbol_matrix = render_equation_part(font_height, new_y_origin, cursor_inside, equation_part.width() + 5, 0, 0, 2);
			symbol_matrix.pop_back_x();

			// add opening bracket
			if (symbol_matrix.height() == 6) symbol_matrix.extend_left(Graphics::SYMBOLS_6_HIGH.at(40));
			else {
				DynamicBitset bracket_raw(2, false);
				bracket_raw.extend(symbol_matrix.height() - 4, true);
				bracket_raw.extend(2, false);
				Bitset2D bracket_left(1, bracket_raw);
				bracket_left.extend_left(1, false);
				bracket_left.extend_right(3, false);
				bracket_left.set_bit(3, 0, true);
				bracket_left.set_bit(2, 1, true);
				bracket_left.set_bit(3, bracket_left.height() - 1, true);
				bracket_left.set_bit(2, bracket_left.height() - 2, true);
				symbol_matrix.extend_left(bracket_left);
			}

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin);
		}

		// closed bracket
		else if (value == ')') {
			if (equation_part.height() == 6) equation_part.extend_right(Graphics::SYMBOLS_6_HIGH.at(41));
			else {
				DynamicBitset bracket_raw(2, false);
				bracket_raw.extend(equation_part.height() - 4, true);
				bracket_raw.extend(2, false);
				Bitset2D bracket_right(1, bracket_raw);
				bracket_right.extend_left(3, false);
				bracket_right.extend_right(1, false);
				bracket_right.set_bit(1, 0, true);
				bracket_right.set_bit(2, 1, true);
				bracket_right.set_bit(1, bracket_right.height() - 1, true);
				bracket_right.set_bit(2, bracket_right.height() - 2, true);
				equation_part.extend_right(bracket_right);
			}
			if (type == 2) {
				if (cursor_inside) {
					cursor_inside_ref = true;
					_cursor_data.x += cursor_offset_x;
					_cursor_data.y += cursor_offset_y;
					if (cursor_alignment == 1) _cursor_data.y += y_origin;
					else if (cursor_alignment == 2) _cursor_data.y -= equation_part.height() - y_origin;
				}
				return equation_part;
			}
		}

		// Abs
		else if (value == KEY_ABS) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(font_height, new_y_origin, cursor_inside, equation_part.width() + 5);
			symbol_matrix.extend_up(1, false);

			Bitset2D abs_symbol = Bitset2D(5, symbol_matrix.height(), false);
			abs_symbol.set_column(2, DynamicBitset(symbol_matrix.height(), true));
			symbol_matrix.extend_left(abs_symbol);
			symbol_matrix.extend_right(abs_symbol);

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin + 1);
		}

		else if (value == KEY_MOD) {
			symbol_matrix = table->at(KEY_DIVIDE);
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table->at('R'));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_up(y_origin, false);
			symbol_matrix.extend_down(equation_part.height() - symbol_matrix.height(), false);
			equation_part.extend_right(symbol_matrix);
		}

		// logn
		else if (value == KEY_LOGN) {
			symbol_matrix.extend_right(table->at('l'));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table->at('o'));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table->at('g'));
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);

			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(6, new_y_origin, cursor_inside, equation_part.width(), 5, 1);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, -5);

			symbol_matrix = render_equation_part(font_height, new_y_origin, cursor_inside, equation_part.width() + 5);

			DynamicBitset bracket_raw(symbol_matrix.height() - 4, true);
			bracket_raw.extend_left(2, false);
			bracket_raw.extend(2, false);
			Bitset2D bracket_left(1, bracket_raw);
			bracket_left.extend_left(1, false);
			bracket_left.extend_right(3, false);
			bracket_left.set_bit(3, 0, true);
			bracket_left.set_bit(2, 1, true);
			bracket_left.set_bit(3, bracket_left.height() - 1, true);
			bracket_left.set_bit(2, bracket_left.height() - 2, true);
			symbol_matrix.extend_left(bracket_left);
			Bitset2D bracket_right(1, bracket_raw);
			bracket_right.extend_left(3, false);
			bracket_right.extend_right(1, false);
			bracket_right.set_bit(1, 0, true);
			bracket_right.set_bit(2, 1, true);
			bracket_right.set_bit(1, bracket_right.height() - 1, true);
			bracket_right.set_bit(2, bracket_right.height() - 2, true);
			symbol_matrix.extend_right(bracket_right);

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin);
		}

		// fraction or mixedfraction
		else if (value == KEY_FRACTION || value == KEY_MIXED_FRACTION) {
			// render front
			if (value == KEY_MIXED_FRACTION) {
				Bitset2D front = render_restricted(6, &Graphics::SYMBOLS_6_HIGH, cursor_inside, equation_part.width() - 1, font_height == 9, true);
				extend_bitset_left_and_match_y_origin(equation_part, y_origin, front, -(font_height == 9));
			}

			// render top and bottom
			uint8_t fraction_line_height = (font_height == 9) ? 3 : 2;
			int32_t new_y_origin = 0;
			bool cursor_in_top = false;
			bool cursor_in_bottom = false;
			auto top = render_equation_part(6, new_y_origin, cursor_in_top, equation_part.width(), fraction_line_height, 2);
			auto bottom = render_equation_part(6, new_y_origin, cursor_in_bottom, equation_part.width(), 3 + fraction_line_height, 1);
			cursor_inside = cursor_in_top || cursor_in_bottom || cursor_inside;

			// extend the top and bottom to the same width
			int32_t diff = bottom.width() - top.width();
			if (diff > 0) {
				top.extend_right(diff / 2, false);
				top.extend_left((diff + 1) / 2, false);
				if (cursor_in_top) _cursor_data.x += (diff + 1) / 2;
			} else if (diff < 0) {
				bottom.extend_right(-diff / 2, false);
				bottom.extend_left((-diff + 1) / 2, false);
				if (cursor_in_bottom) _cursor_data.x += (-diff + 1) / 2;
			}
			// combine top and bottom with a fraction line
			for (uint32_t i = 0; i < top.width(); i++) {
				DynamicBitset column = top[i];
				column.push_back(false);
				column.push_back(true);
				column.push_back(false);
				column.extend(bottom[i]);
				symbol_matrix.push_back(column);
			}

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, top.height() - fraction_line_height);
		}

		// Sqrt
		else if (value == KEY_SQRT) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(font_height, new_y_origin, cursor_inside, equation_part.width() + 4);
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_up(1, false);
			symbol_matrix.extend_up(1, true);

			uint32_t split_point;
			if (symbol_matrix.height() > 29) split_point = 15;
			else split_point = symbol_matrix.height() / 2;
			DynamicBitset root_lower = DynamicBitset(split_point, false);
			DynamicBitset root_upper = DynamicBitset(split_point, true);
			root_lower.extend(symbol_matrix.height() - split_point, true);
			root_upper.extend(symbol_matrix.height() - split_point, false);
			symbol_matrix.push_front(root_upper);
			symbol_matrix.push_front(root_lower);
			symbol_matrix.extend_left(2, false);
			symbol_matrix.set_bit(0, symbol_matrix.height() - 3, true);
			symbol_matrix.set_bit(1, symbol_matrix.height() - 2, true);

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin + 2);
		}

		// x^n
		else if (value == KEY_POWER || value == KEY_POWER10 || value == KEY_EXP) {
			int32_t new_y_origin = 0;
			if (value == KEY_POWER10) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table->at(KEY_POWER10), 0);
			else if (value == KEY_EXP) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table->at(KEY_EULER), 0);
			else {
				if (_render_index == 0) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table->at(KEY_EMPTY), 0);
				else {
					KEY last_val = _equation.at(_render_index - 1);
					if (last_val > 47 && last_val < 58 || last_val > 64 && last_val < 91 || last_val > 96 && last_val < 123 ||
					    last_val == 191 && (last_rendered != KEY_POWER && last_rendered != KEY_POWER10 && last_rendered != KEY_EXP) ||
					    Utils::in_key_set(last_val, _values_before_exponent)) equation_part.pop_back_x();
					else extend_bitset_left_and_match_y_origin(equation_part, y_origin, table->at(KEY_EMPTY), 0);
				}
			}
			symbol_matrix = render_equation_part(6, new_y_origin, cursor_inside, equation_part.width(), 4 - y_origin, 2);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, symbol_matrix.height() + y_origin - 4);
		}

		// *10^n
		else if (value == KEY_SCIENTIFIC_E) {
			symbol_matrix = table->at(KEY_SCIENTIFIC_E);
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table->at(KEY_POWER10));
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// periodic
		else if (value == KEY_PERIODIC) {
			symbol_matrix = render_restricted(font_height, table, cursor_inside, equation_part.width() - 1, 0, false);
			symbol_matrix.extend_up(1, false);
			symbol_matrix.extend_up(1, true);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 2);
		}

		// rootn
		else if (value == KEY_ROOTN) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(6, new_y_origin, cursor_inside, equation_part.width(), 2, 2);
			symbol_matrix.extend_down(7, false);
			symbol_matrix.set_bit(symbol_matrix.width() - 2, symbol_matrix.height() - 3, true);
			symbol_matrix.set_bit(symbol_matrix.width() - 1, symbol_matrix.height() - 2, true);

			Bitset2D radicant = render_equation_part(font_height, new_y_origin, cursor_inside, equation_part.width() + symbol_matrix.width() + 2, 0);
			radicant.extend_right(1, false);
			radicant.extend_up(1, false);
			radicant.extend_up(1, true);

			uint32_t split_point;
			if (radicant.height() > 29) split_point = 15;
			else split_point = radicant.height() / 2;
			DynamicBitset root_lower = DynamicBitset(split_point, false);
			DynamicBitset root_upper = DynamicBitset(split_point, true);
			root_lower.extend(radicant.height() - split_point, true);
			root_upper.extend(radicant.height() - split_point, false);
			radicant.push_front(root_upper);
			radicant.push_front(root_lower);
			int32_t diff = symbol_matrix.height() - radicant.height();
			radicant.extend_up(diff, false);
			symbol_matrix.extend_right(radicant);

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin + 2 + diff);
		}

		// symbol keys
		else if (value == KEY_NEXT_VAL || value == KEY_SYMBOL_END) {
			if (type == 2) {
				_render_index--;
				if (cursor_inside) {
					cursor_inside_ref = true;
					_cursor_data.x += cursor_offset_x;
					_cursor_data.y += cursor_offset_y;
					if (cursor_alignment == 1) _cursor_data.y += y_origin;
					else if (cursor_alignment == 2) _cursor_data.y -= equation_part.height() - y_origin;
				}
				return equation_part;
			}
			break;
		}

		// newline
		else if (value == '\n') {
			if (type == 0) {
				_render_index++;
				int32_t new_y_origin = 0;
				symbol_matrix = render_equation_part(font_height, new_y_origin, cursor_inside, 0, equation_part.height() + 1 - y_origin, 1, 0);
				equation_part.extend_down(1, false);
				equation_part.extend_down(symbol_matrix);
			} else Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		}

		// Fonts
		// TODO: Font 8
		else if (value == KEY_FONT_5_HIGH) {
			table = &Graphics::SYMBOLS_5_HIGH;
			font_height = 5;
		} else if (value == KEY_FONT_6_HIGH) {
			table = &Graphics::SYMBOLS_6_HIGH;
			font_height = 6;
		} else if (value == KEY_FONT_7_HIGH) {
			table = &Graphics::SYMBOLS_7_HIGH;
			font_height = 7;
		} else if (value == KEY_FONT_8_HIGH) {
			table = &Graphics::SYMBOLS_7_HIGH;
			font_height = 7;
		} else if (value == KEY_FONT_9_HIGH) {
			table = &Graphics::SYMBOLS_9_HIGH;
			font_height = 9;
		}

		// Ran#
		else if (value == KEY_RAN) {
			symbol_matrix = Graphics::create_text("Ran#", *table, 1);
			symbol_matrix.extend_up(y_origin, false);
			symbol_matrix.extend_down(equation_part.height() - symbol_matrix.height(), false);
			equation_part.extend_right(symbol_matrix);
		}

		// any other KEY
		else {
			if (table->count(value) != 0) symbol_matrix = table->at(value);
			else symbol_matrix = table->at(0);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// add space after the symbol
		equation_part.push_back(DynamicBitset(equation_part.height(), false));

		last_rendered = value;
	}
	// special case: cursor at the end of the equation
	if (_render_index == _cursor_index) {
		_cursor_data = { equation_part.width() - 1, 0, font_height };
		cursor_inside = true;
	}
	if (cursor_inside) {
		cursor_inside_ref = true;
		_cursor_data.x += cursor_offset_x;
		_cursor_data.y += cursor_offset_y;
		if (cursor_alignment == 1) _cursor_data.y += y_origin;
		else if (cursor_alignment == 2) _cursor_data.y -= equation_part.height() - y_origin;
	}
	if (equation_part.width() == 1 && type == 1) {
		equation_part.extend_right(table->at(KEY_EMPTY));
		equation_part.extend_right(1, false);
	}
	return equation_part;
}

Bitset2D Equation::render_restricted(uint8_t font_height, FONT* table, bool& cursor_inside, int32_t cursor_offset_x, int8_t cursor_offset_y, bool mixed_fraction)
{
	Bitset2D symbol_matrix = Bitset2D(1, font_height, false);
	uint8_t depth = 0;
	uint8_t decimal = 0;
	_render_index++;
	while (_render_index < _equation.size()) {
		KEY key = _equation.at(_render_index);
		if (_render_index == _cursor_index) {
			_cursor_data = { cursor_offset_x + symbol_matrix.width(), cursor_offset_y, font_height };
			cursor_inside = true;
		}
		if (key > 47 && key < 58 || mixed_fraction && (key == ',' && decimal == 0 && (decimal = 1) || key == KEY_SCIENTIFIC_E && decimal != 0 && (decimal = 2) || key == '-' || key == KEY_NEGATE)) {
			symbol_matrix.extend_right(table->at(key));
			symbol_matrix.extend_right(1, false);
			_render_index++;
			continue;
		} else if (key == KEY_SYMBOL_END) {
			if (depth == 0 && !mixed_fraction) break;
			depth--;
		} else if (mixed_fraction && key == KEY_NEXT_VAL && depth == 0) {
			break;
		} else if (Utils::in_key_set(key, _symbols)) {
			depth++;
		}
		_equation.erase(_equation.begin() + _render_index);
		if (_cursor_index > _render_index) _cursor_index--;
	}

	if (symbol_matrix.width() == 1) {
		symbol_matrix.extend_right(table->at(KEY_EMPTY));
		symbol_matrix.extend_right(1, false);
	}

	return symbol_matrix;
}

void Equation::extend_bitset_left_and_match_y_origin(Bitset2D& bitset, int32_t& y_origin, const Bitset2D& bitset_new, int32_t y_origin_new)
{
	Bitset2D bitset_new_copy = bitset_new;
	if (y_origin < y_origin_new) {
		bitset.extend_up(y_origin_new - y_origin, false);
		y_origin = y_origin_new;
	} else bitset_new_copy.extend_up(y_origin - y_origin_new, false);
	if (bitset.height() < bitset_new_copy.height()) bitset.extend_down(bitset_new_copy.height() - bitset.height(), false);
	else bitset_new_copy.extend_down(bitset.height() - bitset_new_copy.height(), false);
	bitset.extend_right(bitset_new_copy);
}

std::string Equation::to_string_simple() const
{
	std::string res = std::to_string(_cursor_index) + " -";
	for (uint32_t i = 0; i < _equation.size(); i++) {
		res += (_cursor_index == i ? "|" : " ") + std::to_string(_equation[i]);
	}
	if (_cursor_index == _equation.size()) res += "|";
	return res + "                                                                                                   ";
}


void Equation::add_value_raw(KEY value, uint8_t mode, KEY_SET first_child)
{
	// TODO: improve
	if (mode == 0 || mode == 3) {
		_equation.insert(_equation.begin() + _cursor_index++, value);
		_equation.insert(_equation.begin() + _cursor_index, KEY_SYMBOL_END);
		if (mode == 3) _equation.insert(_equation.begin() + _cursor_index, KEY_NEXT_VAL);
	} else if (mode == 1) {
		_equation.insert(_equation.begin() + _cursor_index++, value);
		_equation.insert(_equation.begin() + get_value_end_right(_cursor_index), KEY_SYMBOL_END);
	} else if (mode == 2 || mode == 5) {
		_equation.insert(_equation.begin() + _cursor_index++, value);
		_equation.insert(_equation.begin() + _cursor_index, first_child.begin(), first_child.end());
		_cursor_index += first_child.size();
		if (mode == 2) _equation.insert(_equation.begin() + _cursor_index, KEY_SYMBOL_END);
		else {
			_equation.insert(_equation.begin() + _cursor_index, KEY_NEXT_VAL);
			_equation.insert(_equation.begin() + get_value_end_right(_cursor_index), KEY_SYMBOL_END);
		}
	} else if (mode == 4 || mode == 6) {
		_equation.insert(_equation.begin() + get_value_end_left(_cursor_index++, mode == 6), value);
		_equation.insert(_equation.begin() + _cursor_index++, KEY_NEXT_VAL);
		uint32_t i = get_value_end_right(_cursor_index);
		_equation.insert(_equation.begin() + i, KEY_SYMBOL_END);
		if (mode == 6) _equation.insert(_equation.begin() + i, KEY_NEXT_VAL);
	}
}

uint32_t Equation::get_value_end_left(uint32_t index, bool only_decimal)
{
	if (index == 0) return 0;
	index--;
	KEY val = _equation.at(index);
	if (val > 47 && val < 58 || val == ',' || val == KEY_SCIENTIFIC_E) {
		for (; index > 0; index--) {
			val = _equation.at(index);
			if (!(val > 47 && val < 58 || val == ',' || val == KEY_SCIENTIFIC_E || val == '-' || val == KEY_NEGATE)) return ++index;
		}
	} else if (only_decimal) {
		return ++index;
	} else if (val == ')') {
		uint8_t depth = 0;
		for (; index > 0; index--) {
			val = _equation.at(index);
			if (val == ')') depth++;
			else if (Utils::in_key_set(val, _bracket_keys)) {
				if (depth == 1) break;
				depth--;
			}
		}
	} else if (val == KEY_SYMBOL_END) {
		uint8_t depth = 0;
		for (; index > 0; index--) {
			val = _equation.at(index);
			if (val == KEY_SYMBOL_END) depth++;
			else if (Utils::in_key_set(val, _symbols)) {
				if (depth == 1) break;
				depth--;
			}
		}
	} else return ++index;
	return index;
}

uint32_t Equation::get_value_end_right(uint32_t index)
{
	if (index == _equation.size()) return index;
	KEY val = _equation.at(index);
	if (val > 47 && val < 58 || val == ',' || val == KEY_SCIENTIFIC_E) {
		for (; index < _equation.size(); index++) {
			val = _equation.at(index);
			if (!(val > 47 && val < 58 || val == ',' || val == KEY_SCIENTIFIC_E)) break;
		}
	} else if (Utils::in_key_set(val, _bracket_keys)) {
		uint8_t depth = 0;
		index++;
		for (; index < _equation.size(); index++) {
			val = _equation.at(index);
			if (Utils::in_key_set(val, _bracket_keys)) depth++;
			else if (val == ')') {
				if (depth == 0) return ++index;
				depth--;
			}
		}
	} else if (Utils::in_key_set(val, _symbols)) {
		uint8_t depth = 0;
		index++;
		for (; index < _equation.size(); index++) {
			val = _equation.at(index);
			if (Utils::in_key_set(val, _symbols)) depth++;
			else if (val == KEY_SYMBOL_END) {
				if (depth == 0) return ++index;
				depth--;
			}
		}
	}
	return index;
}


Number* Equation::to_number_part(KEY expected_ending)
{
	if (expected_ending != 0) _calculate_index++;
	std::vector<CalculateNode> calculation;
	bool numExpected = true;
	NumberParser number_parser = NumberParser();
	for (; _calculate_index < _equation.size(); _calculate_index++) {
		KEY value = _equation.at(_calculate_index);

		if (!number_parser.add_digit(value)) {
			if (number_parser.get_value_cnt() != 0) calculation.push_back(CalculateNode(number_parser.get_number(), 0, number_parser.get_value_cnt()));

			switch (value) {
			// symbols that need to be ended with SYMBOL_END
			case 0: Error::throw_error(Error::ErrorType::SYNTAX_ERROR); break;
			case KEY_ABS: calculation.push_back(CalculateNode(to_number_part(KEY_SYMBOL_END)->abs(), 0, _calculate_index)); break;
			case KEY_LOGN: {
				Number* result = to_number_part(KEY_NEXT_VAL);
				calculation.push_back(CalculateNode(to_number_part(KEY_SYMBOL_END)->log(result), 0, _calculate_index));
				break;
			}
			case KEY_FRACTION: calculation.push_back(CalculateNode(to_number_part(KEY_NEXT_VAL)->divide(to_number_part(KEY_SYMBOL_END)), 0, _calculate_index)); break;
			case KEY_SQRT: calculation.push_back(CalculateNode(to_number_part(KEY_SYMBOL_END)->sqrt(), 0, _calculate_index)); break;
			case KEY_MIXED_FRACTION: calculation.push_back(CalculateNode(to_number_part(KEY_NEXT_VAL)->add(to_number_part(KEY_NEXT_VAL)->divide(to_number_part(KEY_SYMBOL_END))), 0, _calculate_index)); break;
			case KEY_ROOTN: {
				Number* result = to_number_part(KEY_NEXT_VAL);
				calculation.push_back(CalculateNode(to_number_part(KEY_SYMBOL_END)->root(result), 0, _calculate_index));
				break; //!
			}
			case KEY_POWER10: calculation.push_back(CalculateNode((new Number(10))->pow(to_number_part(KEY_SYMBOL_END)), 0, _calculate_index)); break;
			case KEY_EXP: calculation.push_back(CalculateNode(to_number_part(KEY_SYMBOL_END)->exp(), 0, _calculate_index)); break;
			// Symbols that have an open bracket at the end
			case '(': calculation.push_back(CalculateNode(to_number_part(')'), 0, _calculate_index)); break;
			case KEY_LOG: calculation.push_back(CalculateNode((new Number(10))->log(to_number_part(')')), 0, _calculate_index)); break;
			case KEY_LN: calculation.push_back(CalculateNode(to_number_part(')')->ln(), 0, _calculate_index)); break;
			case KEY_SIN: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->sin(), 0, _calculate_index)); break;
			case KEY_COS: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->cos(), 0, _calculate_index)); break;
			case KEY_TAN: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->tan(), 0, _calculate_index)); break;
			case KEY_ASIN: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->asin(), 0, _calculate_index)); break;
			case KEY_ACOS: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->acos(), 0, _calculate_index)); break;
			case KEY_ATAN: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->atan(), 0, _calculate_index)); break;
			case KEY_SINH: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->sinh(), 0, _calculate_index)); break;
			case KEY_COSH: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->cosh(), 0, _calculate_index)); break;
			case KEY_TANH: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->tanh(), 0, _calculate_index)); break;
			case KEY_ASINH: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->asinh(), 0, _calculate_index)); break;
			case KEY_ACOSH: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->acosh(), 0, _calculate_index)); break;
			case KEY_ATANH: calculation.push_back(CalculateNode(to_number_part(')')->to_angle((_settings >> 2) & 3)->atanh(), 0, _calculate_index)); break;
			case KEY_POL: calculation.push_back(CalculateNode(to_number_part(':')->pol(to_number_part(')')), 0, _calculate_index)); break;
			case KEY_REC: calculation.push_back(CalculateNode(to_number_part(':')->rec(to_number_part(')')), 0, _calculate_index)); break;
			case KEY_RND: calculation.push_back(CalculateNode(to_number_part(')')->round(), 0, _calculate_index)); break;
			case KEY_GCD: calculation.push_back(CalculateNode(to_number_part(':')->gcd(to_number_part(')')), 0, _calculate_index)); break;
			case KEY_LCM: calculation.push_back(CalculateNode(to_number_part(':')->lcm(to_number_part(')')), 0, _calculate_index)); break;
			case KEY_INT: calculation.push_back(CalculateNode(to_number_part(')')->to_int(), 0, _calculate_index)); break;
			case KEY_INTG: calculation.push_back(CalculateNode(to_number_part(')')->floor(), 0, _calculate_index)); break;
			case KEY_RAN_INT: calculation.push_back(CalculateNode(to_number_part(':')->ran_int(to_number_part(')')), 0, _calculate_index)); break;
			// random
			case KEY_RAN: calculation.push_back(CalculateNode(to_number_part(KEY_SYMBOL_END)->ran(), 0, _calculate_index)); break;
			// symbols that perform an operation on the last number
			case KEY_POWER:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->pow(to_number_part(KEY_SYMBOL_END));
				break;
			case '!':
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->factorial();
				break;
			case '%':
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->divide(new Number(100));
				break;
			case KEY_DEGREE:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->from_angle(0);
				break;
			case KEY_RADIAN:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->from_angle(1);
				break;
			case KEY_GRADIAN:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->from_angle(2);
				break;
			default:
				if (value == expected_ending) {
					break;
				} else if (value == ')' || value == ':' || value == KEY_NEXT_VAL || value == KEY_SYMBOL_END) {
					Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
					return new Number();
				} else if (Utils::in_key_set(value, _allowed_calculate_operations)) {
					calculation.push_back(CalculateNode(new Number(), value, _calculate_index));
				} else if (value > 64 && value < 91 || value > 96 && value < 123) {
					calculation.push_back(CalculateNode(Number::from_key(value), 0, _calculate_index));
				}
			}
			if (Error::error_thrown()) {
				_cursor_index = _calculate_index;
				return new Number();
			}
		}
	}
	if (number_parser.get_value_cnt() != 0) calculation.push_back(CalculateNode(number_parser.get_number(), 0, number_parser.get_value_cnt()));

	if (calculation.size() == 0) {
		Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		_cursor_index = _calculate_index;
		return new Number();
	}

	// handle negative numbers
	uint8_t add_i = 0;
	bool negative = false;
	bool operation = true;
	for (uint32_t i = 0; i < calculation.size(); i++) {
		uint8_t op = calculation.at(i).operation;
		if (op != 0) {
			if (!operation) operation = true;
			else {
				if (op == '-' || op == KEY_NEGATE) {
					negative = !negative;
					calculation.erase(calculation.begin() + i--);
				} else if (op != '+') {
					Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
					_cursor_index = i;
					return new Number();
				}
			}
		} else {
			if (negative) calculation.at(i).value->negate();
			negative = false;
			operation = false;
		}
	}

	// TODO: metric conversion

	// multiplication without sign
	operation = true;
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 0) {
			operation = true;
		} else {
			if (!operation) {
				// TODO: automatic brackets
				// if (i > 1 && calculation.at(i - 2).operation == 72) {
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i + 1, new EquationNode{ ')' });
				//	equation.insert(equation.begin() + calculation.at(i - 1).equation_index + add_i++, new EquationNode{ 40 });
				//}
				// if (equation.at(calculation.at(i).equation_index + add_i)->value == 110) {
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i + 1, new EquationNode{ ')' });
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i++, new EquationNode{ 40 });
				//}
				calculation.at(i - 1).value->multiply(calculation.at(i).value);
				calculation.erase(calculation.begin() + i--);
			}
			operation = false;
		}
	}

	// TODO: permutation and combination

	// multiplication and division
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 0) {
			if (calculation.at(i).operation == KEY_MULTIPLY) calculation.at(i - 1).value->multiply(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == KEY_DIVIDE) calculation.at(i - 1).value->divide(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == KEY_MOD) calculation.at(i - 1).value->mod(calculation.at(i + 1).value);
			else continue;
			calculation.erase(calculation.begin() + i);
			calculation.erase(calculation.begin() + i--);
		}
	}

	// addition and subtraction
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 0) {
			if (calculation.at(i).operation == '+') calculation.at(i - 1).value->add(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == '-') calculation.at(i - 1).value->subtract(calculation.at(i + 1).value);
			else continue;
			calculation.erase(calculation.begin() + i);
			calculation.erase(calculation.begin() + i--);
		}
	}

	// TODO: logic operators

	return calculation.at(0).value;
}