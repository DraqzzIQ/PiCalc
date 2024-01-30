#include "calculator/Equation.h"

// TIME
const KEY_SET Equation::_allowed_calculate_operations = { 11, 12, 43, 45, 177, 215, 247 };
const KEY_SET Equation::_single_bracket_open_keys = { 24, 26, 40, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 159, 161, 164, 165, 166, 167, 168, 170 };
const KEY_SET Equation::_values_before_exponent = { 41, 33, 29, 11, 15, 16, 17, 18, 171, 178, 169, 172, 173, 174, 175, 176 };
const KEY_SET Equation::_symbols = { 11, 15, 16, 17, 18, 21, 22, 23, 25, 27 };

Equation::Equation()
{
	_equation = KEY_SET(0);
	_cursor_index = 0;
	render_equation();
}

Equation::Equation(KEY_SET& equation)
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

void Equation::set_key_set(KEY_SET& equation)
{
	_equation = equation;
	_cursor_index = 0;
	render_equation();
}

Bitset2D Equation::get_rendered_equation(bool complete)
{
	// change _show_cursor every 500ms if cursor is active
	if (!_cursor_active) _show_cursor = false;
	else if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time = Utils::us_since_boot();
		_show_cursor = !_show_cursor;
	}

	if (complete) return _show_cursor ? _rendered_equation_cursor : _rendered_equation;
	else return _show_cursor ? _rendered_equation_cursor_frame : _rendered_equation_frame;
}

std::string Equation::to_string() const
{
	// TODO
	return "";
}


void Equation::del()
{
	if (_cursor_index == 0) return;
	KEY val = _equation.at(--_cursor_index);
	if (Utils::in_key_set(val, _symbols)) {
		_equation.erase(_equation.begin() + _cursor_index);
		while (true) {
			val = _equation.at(_cursor_index);
			if (val == 190) _equation.erase(_equation.begin() + _cursor_index);
			else if (val == 191) {
				_equation.erase(_equation.begin() + _cursor_index);
				break;
			} else if (Utils::in_key_set(val, _symbols)) {
				while (_equation.at(_cursor_index) != 191) _cursor_index++;
			} else _cursor_index++;
		}
	} else if (val != 190 && val != 191) {
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
	// TODO
	for (uint32_t i = _cursor_index - 1; i > 0; i--) {
		if (_equation.at(i) == 190) {
			_cursor_index = i;
			render_equation();
			return;
		} else if (_equation.at(i) == 10) {
			uint32_t new_line_index = i;
			i--;
			while (i > 0 && _equation.at(i) != 10) i--;
			_cursor_index -= new_line_index;
			if (i + _cursor_index > new_line_index) _cursor_index = new_line_index;
			else _cursor_index += i;
			render_equation();
			return;
		}
	}
}

void Equation::move_cursor_down()
{
	// TODO
	for (uint32_t i = _cursor_index; i < _equation.size(); i++) {
		if (_equation.at(i) == 190) {
			_cursor_index = i + 1;
			render_equation();
			return;
		} else if (_equation.at(i) == 10) {
			uint32_t new_line_index = i;
			i--;
			while (i < 0 && _equation.at(i) != 10) i--;
			_cursor_index -= new_line_index;
			if (i + _cursor_index > new_line_index) _cursor_index = new_line_index;
			else _cursor_index += i;
			return;
		}
	}
}

void Equation::add_value(KEY keypress)
{
	// TODO: restrictions
	switch (keypress) {
	case 11: add_value_raw(11, 1); break;
	case 13: add_value_raw(22, 1, false, KEY_SET{ 51 }); break;
	case 14: add_value_raw(22, 1, false, KEY_SET{ 28, 49 }); break;
	case 15: add_value_raw(15, 2, true); break;
	case 16: add_value_raw(16, 2, true); break;
	case 18: add_value_raw(18, 1); break;
	case 20: add_value_raw(22, 1, false, KEY_SET{ 50 }); break;
	case 22: add_value_raw(22, 1); break;
	case 17: add_value_raw(17, 3, true); break;
	case 19: add_value_raw(23, 2, false, KEY_SET{ 51 }); break;
	case 21: add_value_raw(21, 1); break; // condition
	case 23: add_value_raw(23, 2, true); break;
	case 25: add_value_raw(25, 1); break;
	case 27: add_value_raw(27, 1); break;
	default: _equation.insert(_equation.begin() + _cursor_index++, keypress); break;
	}
	render_equation();
}


void Equation::set_variable_list(std::vector<Number*> variables)
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
	_rendered_equation = render_equation_part(Graphics::SYMBOLS_9_HIGH, y_origin, cursor_in_equation, 0, 0, 1, 0);
	_rendered_equation.extend_right(1, false);

	// add the cursor to the equation
	_rendered_equation_cursor = _rendered_equation;
	_rendered_equation_cursor.set(_cursor_data.x, _cursor_data.y, Bitset2D(2, _cursor_data.size, true), false);

	// recalculate frame position
	if (_cursor_data.x < _frame_x + 3) _frame_x = _cursor_data.x < 3 ? 0 : _cursor_data.x - 3;
	else if (_cursor_data.x > _frame_x + _frame_width - 4) _frame_x = _cursor_data.x - _frame_width + 4;
	if (_cursor_data.y < _frame_y + 3) _frame_y = _cursor_data.y < 3 ? 0 : _cursor_data.y - 3;
	else if (_cursor_data.y + _cursor_data.size > _frame_y + _frame_height - 2) _frame_y = _cursor_data.y - _frame_height + 2 + _cursor_data.size;

	// get a part of the rendered equation with width frame_width and height frame_height
	_rendered_equation.copy(_frame_x, _frame_y, _frame_width, _frame_height, _rendered_equation_frame);
	_rendered_equation_cursor.copy(_frame_x, _frame_y, _frame_width, _frame_height, _rendered_equation_cursor_frame);
}

Bitset2D Equation::render_equation_part(FONT& table, int32_t& y_origin, bool& cursor_inside_ref, int8_t cursor_offset_x, int8_t cursor_offset_y, uint8_t cursor_alignment, uint8_t type)
{
	uint8_t font_height = table.at(0).height();
	Bitset2D equation_part(1, font_height, false);
	bool cursor_inside = false;
	y_origin = 0;
	if (type == 1) _render_index++;

	for (; _render_index < _equation.size(); _render_index++) {
		Bitset2D symbol_matrix;
		KEY value = _equation.at(_render_index);
		if (_render_index == _cursor_index) {
			_cursor_data = { equation_part.width() - 1, 0, font_height };
			cursor_inside = true;
		}

		// any symbol with an open bracket at the end
		if (Utils::in_key_set(value, _single_bracket_open_keys) && value != 40) {
			// only render the text before the bracket, then change the value to 40 for the other case to render the actual bracket
			KEY_SET keys = Graphics::key_text.at(value);
			for (uint8_t j = 0; j < keys.size(); j++) {
				symbol_matrix.extend_right(table.at(keys.at(j)));
				symbol_matrix.extend_right(1, false);
			}
			symbol_matrix.extend_up(y_origin, false);
			symbol_matrix.extend_down(equation_part.height() - symbol_matrix.height(), false);
			equation_part.extend_right(symbol_matrix);
			value = 40;
		}

		// open bracket
		if (value == 40) {
			// render everything until the closing bracket
			int32_t new_y_origin = 0;
			_render_index++;
			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width() + 5, 0, 0, 2);
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
		else if (value == 41) {
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
		else if (value == 11) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width() + 5);
			symbol_matrix.extend_up(1, false);

			Bitset2D abs_symbol = Bitset2D(5, symbol_matrix.height(), false);
			abs_symbol.set_column(2, DynamicBitset(symbol_matrix.height(), true));
			symbol_matrix.extend_left(abs_symbol);
			symbol_matrix.extend_right(abs_symbol);

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin + 1);
		}

		// logn
		else if (value == 15) {
			symbol_matrix.extend_right(table.at(51));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table.at(54));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table.at(46));
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);

			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_inside, equation_part.width(), 5, 1);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, -5);

			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width() + 5);

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
		else if (value == 16 || value == 17) {
			// render top and bottom
			uint8_t fraction_line_height = (font_height == 9) ? 3 : 2;
			int32_t new_y_origin = 0;
			if (value == 131) {
				auto front = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_inside, equation_part.width(), font_height == 9);
				extend_bitset_left_and_match_y_origin(equation_part, y_origin, front, -(font_height == 9));
			}
			bool cursor_in_top = false;
			bool cursor_in_bottom = false;
			auto top = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_in_top, equation_part.width(), fraction_line_height, 2);
			auto bottom = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_in_bottom, equation_part.width(), 3 + fraction_line_height, 1);
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
		else if (value == 18) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width() + 4);
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
		else if (value == 22 || value == 25 || value == 27) {
			int32_t new_y_origin = 0;
			if (value == 25) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(25), 0);
			else if (value == 27) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(27), 0);
			else {
				KEY last_val = _equation.at(_render_index - 1);
				if (_render_index == 0 || !(last_val > 47 && last_val < 58 || last_val > 64 && last_val < 91 || last_val > 96 && last_val < 123) && !Utils::in_key_set(last_val, _values_before_exponent)) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(127), 0);
				else equation_part.pop_back_x();
			}
			symbol_matrix = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_inside, equation_part.width(), 4, 2);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, symbol_matrix.height() - 4);
		}

		// *10^n
		else if (value == 171) {
			symbol_matrix = table.at(171);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// periodic
		else if (value == 21) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width(), 0);
			symbol_matrix.extend_up(1, false);
			symbol_matrix.extend_up(1, true);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 2);
		}

		// rootn
		else if (value == 23) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_inside, equation_part.width(), 2, 2);
			symbol_matrix.extend_down(7, false);
			symbol_matrix.set_bit(symbol_matrix.width() - 2, symbol_matrix.height() - 3, true);
			symbol_matrix.set_bit(symbol_matrix.width() - 1, symbol_matrix.height() - 2, true);

			Bitset2D radicant = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width() + symbol_matrix.width() + 2, 0);
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
		else if (value == 190 || value == 191) {
			break;
		}

		// newline
		else if (value == 10) {
			if (type == 0) {
				int32_t new_y_origin = 0;
				symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, 0, equation_part.height(), 1, 0);
				equation_part.extend_down(1, false);
				equation_part.extend_down(symbol_matrix);
			} else Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		}

		// any other KEY
		else {
			if (table.count(value) != 0) symbol_matrix = table.at(value);
			else symbol_matrix = table.at(63);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// add space after the symbol
		equation_part.push_back(DynamicBitset(equation_part.height(), false));
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
		equation_part.extend_right(table.at(127));
		equation_part.extend_right(1, false);
	}
	return equation_part;
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


void Equation::add_value_raw(KEY value, uint8_t child_cnt, bool add_value_to_first_child, KEY_SET first_child)
{
	if (add_value_to_first_child) {
		add_value_to_first_child = false;
		uint32_t i = _cursor_index++;
		for (; i > 0; i--) {
			KEY val = _equation.at(i - 1);
			if (!(val > 47 && val < 58 || val == 44 || val == 172)) break;
			add_value_to_first_child = true;
		}
		_equation.insert(_equation.begin() + i, value);
	} else {
		_equation.insert(_equation.begin() + _cursor_index++, value);
		_equation.insert(_equation.begin() + _cursor_index, first_child.begin(), first_child.end());
		_cursor_index += first_child.size();
	}
	_equation.insert(_equation.begin() + _cursor_index, 191);
	for (; child_cnt > 1; child_cnt--) _equation.insert(_equation.begin() + _cursor_index, 190);
	if (add_value_to_first_child) _cursor_index++;
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
			case 11: calculation.push_back(CalculateNode(to_number_part(191)->abs(), 0, _calculate_index)); break;
			case 15: {
				Number* result = to_number_part(190);
				calculation.push_back(CalculateNode(to_number_part(191)->log(result), 0, _calculate_index));
				break;
			}
			case 16: calculation.push_back(CalculateNode(to_number_part(190)->divide(to_number_part(191)), 0, _calculate_index)); break;
			case 18: calculation.push_back(CalculateNode(to_number_part(191)->sqrt(), 0, _calculate_index)); break;
			case 17: calculation.push_back(CalculateNode(to_number_part(190)->add(to_number_part(190)->divide(to_number_part(191))), 0, _calculate_index)); break;
			case 23: {
				Number* result = to_number_part(190);
				calculation.push_back(CalculateNode(to_number_part(191)->root(result), 0, _calculate_index));
				break; //!
			}
			case 25: calculation.push_back(CalculateNode(to_number_part(191)->pow10(), 0, _calculate_index)); break;
			case 27: calculation.push_back(CalculateNode(to_number_part(191)->exp(), 0, _calculate_index)); break;
			// Symbols that have an open bracket at the end
			case 40: calculation.push_back(CalculateNode(to_number_part(41), 0, _calculate_index)); break;
			case 24: calculation.push_back(CalculateNode(to_number_part(41)->log(), 0, _calculate_index)); break;
			case 26: calculation.push_back(CalculateNode(to_number_part(41)->ln(), 0, _calculate_index)); break;
			case 129: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->sin(), 0, _calculate_index)); break;
			case 130: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->cos(), 0, _calculate_index)); break;
			case 131: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->tan(), 0, _calculate_index)); break;
			case 132: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->asin(), 0, _calculate_index)); break;
			case 133: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->acos(), 0, _calculate_index)); break;
			case 134: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->atan(), 0, _calculate_index)); break;
			case 135: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->sinh(), 0, _calculate_index)); break;
			case 136: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->cosh(), 0, _calculate_index)); break;
			case 137: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->tanh(), 0, _calculate_index)); break;
			case 138: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->asinh(), 0, _calculate_index)); break;
			case 139: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->acosh(), 0, _calculate_index)); break;
			case 140: calculation.push_back(CalculateNode(to_number_part(41)->to_angle((_settings >> 2) & 3)->atanh(), 0, _calculate_index)); break;
			case 165: calculation.push_back(CalculateNode(to_number_part(59)->pol(to_number_part(41)), 0, _calculate_index)); break;
			case 167: calculation.push_back(CalculateNode(to_number_part(59)->rec(to_number_part(41)), 0, _calculate_index)); break;
			case 169: calculation.push_back(CalculateNode(to_number_part(41)->round(), 0, _calculate_index)); break;
			case 160: calculation.push_back(CalculateNode(to_number_part(59)->gcd(to_number_part(41)), 0, _calculate_index)); break;
			case 161: calculation.push_back(CalculateNode(to_number_part(59)->lcm(to_number_part(41)), 0, _calculate_index)); break;
			case 162: calculation.push_back(CalculateNode(to_number_part(41)->to_int(), 0, _calculate_index)); break;
			case 163: calculation.push_back(CalculateNode(to_number_part(41)->floor(), 0, _calculate_index)); break;
			case 164: calculation.push_back(CalculateNode(to_number_part(59)->ran_int(to_number_part(41)), 0, _calculate_index)); break;
			// random
			case 155: calculation.push_back(CalculateNode(to_number_part(191)->ran(), 0, _calculate_index)); break;
			// symbols that perform an operation on the last number
			case 113:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->pow(to_number_part(191));
				break;
			case 85:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->factorial();
				break;
			case 98:
				if (calculation.empty() || calculation.back().operation != 0) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				calculation.back().value->percent();
				break;

			default:
				// TODO: euler, degree, radians
				if (value == expected_ending) {
					break;
				} else if (value == 41 || value == 59 || value == 190 || value == 191) {
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
				if (op == 45 || op == 28) {
					negative = !negative;
					calculation.erase(calculation.begin() + i--);
				} else if (op != 43) {
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

	// metric conversion

	// multiplication without sign
	operation = true;
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 0) {
			operation = true;
		} else {
			if (!operation) {
				// TODO: automatic brackets
				// if (i > 1 && calculation.at(i - 2).operation == 72) {
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i + 1, new EquationNode{ 41 });
				//	equation.insert(equation.begin() + calculation.at(i - 1).equation_index + add_i++, new EquationNode{ 40 });
				//}
				// if (equation.at(calculation.at(i).equation_index + add_i)->value == 110) {
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i + 1, new EquationNode{ 41 });
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i++, new EquationNode{ 40 });
				//}
				calculation.at(i - 1).value->multiply(calculation.at(i).value);
				calculation.erase(calculation.begin() + i--);
			}
			operation = false;
		}
	}

	// permutation and combination

	// multiplication and division
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 0) {
			if (calculation.at(i).operation == 215) calculation.at(i - 1).value->multiply(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == 247) calculation.at(i - 1).value->divide(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == 12) calculation.at(i - 1).value->mod(calculation.at(i + 1).value);
			else continue;
			calculation.erase(calculation.begin() + i);
			calculation.erase(calculation.begin() + i--);
		}
	}

	// addition and subtraction
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 0) {
			if (calculation.at(i).operation == 43) calculation.at(i - 1).value->add(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == 45) calculation.at(i - 1).value->subtract(calculation.at(i + 1).value);
			else continue;
			calculation.erase(calculation.begin() + i);
			calculation.erase(calculation.begin() + i--);
		}
	}

	// logic operators

	return calculation.at(0).value;
}