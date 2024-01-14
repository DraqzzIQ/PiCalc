#include "calculator/Equation.h"

const KEY_SET Equation::_allowed_calculate_operations = { 69, 70, 71, 72, 74, 75, 85, 98, 114, 115, 116, 118, 119, 120, 130, 138, 139, 140, 152, 153, 154, 159, 162, 163, 164 };
const KEY_SET Equation::_single_bracket_open_keys = { 74, 114, 115, 118, 119, 120, 138, 139, 140, 152, 153, 154, 160, 161, 162, 163, 164, 190, 191, 192, 193, 194, 195 };
const KEY_SET Equation::_values_before_exponent = { 75, 85, 102, 106, 109, 110, 111, 127, 128, 131, 155, 156, 165, 186, 187, 188 };
const KEY_SET Equation::_symbols = { 106, 109, 110, 111, 113, 131, 133, 134, 135, 136 };

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
		_last_blink_time += 500000;
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
	if (Chars::in_key_set(val, _symbols)) {
		_equation.erase(_equation.begin() + _cursor_index);
		while (true) {
			val = _equation.at(_cursor_index);
			if (val == 237) _equation.erase(_equation.begin() + _cursor_index);
			else if (val == 238) {
				_equation.erase(_equation.begin() + _cursor_index);
				break;
			} else if (Chars::in_key_set(val, _symbols)) {
				while (_equation.at(_cursor_index) != 238) _cursor_index++;
			} else _cursor_index++;
		}
	} else if (val != 237 && val != 238) {
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
	for (uint32_t i = _cursor_index - 1; i > 0; i--) {
		if (_equation.at(i) == 237) {
			_cursor_index = i;
			render_equation();
			return;
		} else if (_equation.at(i) == 238) {
			return;
		}
	}
}

void Equation::move_cursor_down()
{
	for (uint32_t i = _cursor_index; i < _equation.size(); i++) {
		if (_equation.at(i) == 237) {
			_cursor_index = i + 1;
			render_equation();
			return;
		} else if (Chars::in_key_set(_equation.at(i), _symbols)) {
			return;
		}
	}
}

void Equation::add_value(KEY keypress)
{
	// TODO: restrictions
	switch (keypress) {
	case 106: add_value_raw(106, 1); break;
	case 107: add_value_raw(113, 1, false, KEY_SET{ 3 }); break;
	case 108: add_value_raw(113, 1, false, KEY_SET{ 116, 1 }); break;
	case 109: add_value_raw(109, 2, true); break;
	case 110: add_value_raw(110, 2, true); break;
	case 111: add_value_raw(111, 1); break;
	case 112: add_value_raw(113, 1, false, KEY_SET{ 2 }); break;
	case 113: add_value_raw(113, 1); break;
	case 131: add_value_raw(131, 3, true); break;
	case 132: add_value_raw(134, 2, true); break;
	case 133: add_value_raw(133, 1); break; // condition
	case 134: add_value_raw(134, 2, true); break;
	case 135: add_value_raw(135, 1); break;
	case 136: add_value_raw(136, 1); break;
	default: _equation.insert(_equation.begin() + _cursor_index++, keypress); break;
	}
	render_equation();
}


void Equation::set_variable_list(std::vector<Number*> variables)
{
	_variables = variables;
}

Number* Equation::to_number()
{
	_calculate_index = 0;
	Number* res = to_number_part(95);
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
		if (Chars::in_key_set(value, _single_bracket_open_keys) && value != 74) {
			// only render the text before the bracket, then change the value to 74 for the other case to render the actual bracket
			KEY_SET keys = Graphics::key_text.at(value);
			for (uint8_t j = 0; j < keys.size(); j++) {
				symbol_matrix.extend_right(table.at(keys.at(j)));
				symbol_matrix.extend_right(1, false);
			}
			symbol_matrix.extend_up(y_origin, false);
			symbol_matrix.extend_down(equation_part.height() - symbol_matrix.height(), false);
			equation_part.extend_right(symbol_matrix);
			value = 74;
		}

		// open bracket
		if (value == 74) {
			// render everything until the closing bracket
			int32_t new_y_origin = 0;
			_render_index++;
			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width() + 5, 0, 0, 2);
			symbol_matrix.pop_back_x();

			// add opening bracket
			if (symbol_matrix.height() == 6) symbol_matrix.extend_left(Graphics::SYMBOLS_6_HIGH.at(74));
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
		else if (value == 75) {
			if (equation_part.height() == 6) equation_part.extend_right(Graphics::SYMBOLS_6_HIGH.at(75));
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
			if (type == 2) break;
		}

		// Abs
		else if (value == 106) {
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
		else if (value == 109) {
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
		else if (value == 110 || value == 131) {
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

		// root2
		else if (value == 111) {
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
		else if (value == 113 || value == 135 || value == 136) {
			int32_t new_y_origin = 0;
			if (value == 135) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(135), 0);
			else if (value == 136) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(165), 0);
			else {
				if (_render_index == 0 || !(_equation.at(_render_index - 1) < 69 || Chars::in_key_set(_equation.at(_render_index - 1), _values_before_exponent) != 0)) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(95), 0);
				else equation_part.pop_back_x();
			}
			symbol_matrix = render_equation_part(Graphics::SYMBOLS_6_HIGH, new_y_origin, cursor_inside, equation_part.width(), 4, 2);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, symbol_matrix.height() - 4);
		}

		// *10^n
		else if (value == 127) {
			symbol_matrix = table.at(127);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// periodic
		else if (value == 133) {
			int32_t new_y_origin = 0;
			symbol_matrix = render_equation_part(table, new_y_origin, cursor_inside, equation_part.width(), 0);
			symbol_matrix.extend_up(1, false);
			symbol_matrix.extend_up(1, true);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 2);
		}

		// rootn
		else if (value == 134) {
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

		else if (value == 237 || value == 238) {
			break;
		}

		// any other symbol
		else {
			if (table.count(value) != 0) symbol_matrix = table.at(value);
			else symbol_matrix = table.at(86);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// add space after the symbol
		equation_part.push_back(DynamicBitset(equation_part.height(), false));
	}
	// special case: cursor at the end of the equation
	if (type != 2 && _render_index == _cursor_index) {
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
		equation_part.extend_right(table.at(95));
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
			if (!(val < 10 || val == 82 || val == 127)) break;
			add_value_to_first_child = true;
		}
		_equation.insert(_equation.begin() + i, value);
	} else {
		_equation.insert(_equation.begin() + _cursor_index++, value);
		_equation.insert(_equation.begin() + _cursor_index, first_child.begin(), first_child.end());
		_cursor_index += first_child.size();
	}
	_equation.insert(_equation.begin() + _cursor_index, 238);
	for (; child_cnt > 1; child_cnt--) _equation.insert(_equation.begin() + _cursor_index, 237);
	if (add_value_to_first_child) _cursor_index++;
}


Number* Equation::to_number_part(KEY expected_ending)
{
	if (expected_ending != 95) _calculate_index++;
	std::vector<CalculateNode> calculation;
	bool numExpected = true;
	clear_number();
	for (; _calculate_index < _equation.size(); _calculate_index++) {
		KEY value = _equation.at(_calculate_index);

		if (!add_digit(value)) {
			if (_number_value_cnt != 0) calculation.push_back(CalculateNode(get_number(), 95, _number_value_cnt & 0b00111111));

			if (Chars::in_key_set(value, _symbols)) {
				switch (value) {
				case 95: Error::throw_error(Error::ErrorType::SYNTAX_ERROR); break;
				case 106: calculation.push_back(CalculateNode(to_number_part(238)->abs(), 95, _calculate_index)); break;
				case 109: {
					Number* result = to_number_part(237);
					calculation.push_back(CalculateNode(to_number_part(238)->log(result), 95, _calculate_index));
					break;
				}
				case 110: calculation.push_back(CalculateNode(to_number_part(237)->divide(to_number_part(238)), 95, _calculate_index)); break;
				case 111: calculation.push_back(CalculateNode(to_number_part(238)->sqrt(), 95, _calculate_index)); break;
				case 131: calculation.push_back(CalculateNode(to_number_part(237)->add(to_number_part(237)->divide(to_number_part(238))), 95, _calculate_index)); break;
				case 134: {
					Number* result = to_number_part(237);
					calculation.push_back(CalculateNode(to_number_part(238)->root(result), 95, _calculate_index));
					break; //!
				}
				case 135: calculation.push_back(CalculateNode(to_number_part(238)->pow10(), 95, _calculate_index)); break;
				case 136: calculation.push_back(CalculateNode(to_number_part(238)->exp(), 95, _calculate_index)); break;
				default:
					if (calculation.size() == 0 || calculation.back().operation != 95) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
					switch (value) {
					case 113: calculation.back().value->pow(to_number_part(238)); break;
					case 85: calculation.back().value->factorial(); break;
					case 98: calculation.back().value->percent(); break;
					}
				}
			} else if (Chars::in_key_set(value, _single_bracket_open_keys)) {
				switch (value) {
				case 74: calculation.push_back(CalculateNode(to_number_part(75), 95, _calculate_index)); break;
				case 114: calculation.push_back(CalculateNode(to_number_part(75)->log(), 95, _calculate_index)); break;
				case 115: calculation.push_back(CalculateNode(to_number_part(75)->ln(), 95, _calculate_index)); break;
				case 118: calculation.push_back(CalculateNode(to_number_part(75)->sin(), 95, _calculate_index)); break;
				case 119: calculation.push_back(CalculateNode(to_number_part(75)->cos(), 95, _calculate_index)); break;
				case 120: calculation.push_back(CalculateNode(to_number_part(75)->tan(), 95, _calculate_index)); break;
				case 138: calculation.push_back(CalculateNode(to_number_part(75)->asin(), 95, _calculate_index)); break;
				case 139: calculation.push_back(CalculateNode(to_number_part(75)->acos(), 95, _calculate_index)); break;
				case 140: calculation.push_back(CalculateNode(to_number_part(75)->atan(), 95, _calculate_index)); break;
				case 152: calculation.push_back(CalculateNode(to_number_part(83)->pol(to_number_part(75)), 95, _calculate_index)); break;
				case 153: calculation.push_back(CalculateNode(to_number_part(83)->rec(to_number_part(75)), 95, _calculate_index)); break;
				case 154: calculation.push_back(CalculateNode(to_number_part(75)->round(), 95, _calculate_index)); break;
				case 160: calculation.push_back(CalculateNode(to_number_part(83)->gcd(to_number_part(75)), 95, _calculate_index)); break;
				case 161: calculation.push_back(CalculateNode(to_number_part(83)->lcm(to_number_part(75)), 95, _calculate_index)); break;
				case 162: calculation.push_back(CalculateNode(to_number_part(75)->to_int(), 95, _calculate_index)); break;
				case 163: calculation.push_back(CalculateNode(to_number_part(75)->floor(), 95, _calculate_index)); break;
				case 164: calculation.push_back(CalculateNode(to_number_part(83)->ran_int(to_number_part(75)), 95, _calculate_index)); break;
				case 190: calculation.push_back(CalculateNode(to_number_part(75)->sinh(), 95, _calculate_index)); break;
				case 191: calculation.push_back(CalculateNode(to_number_part(75)->cosh(), 95, _calculate_index)); break;
				case 192: calculation.push_back(CalculateNode(to_number_part(75)->tanh(), 95, _calculate_index)); break;
				case 193: calculation.push_back(CalculateNode(to_number_part(75)->asinh(), 95, _calculate_index)); break;
				case 194: calculation.push_back(CalculateNode(to_number_part(75)->acosh(), 95, _calculate_index)); break;
				case 195: calculation.push_back(CalculateNode(to_number_part(75)->atanh(), 95, _calculate_index)); break;
				}
			} else if (value == expected_ending) {
				break;
			} else if (value == 75 || value == 83 || value == 237 || value == 238) {
				Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				return new Number();
			} else if (Chars::in_key_set(value, _allowed_calculate_operations) || (value > 189 && value < 236)) {
				calculation.push_back(CalculateNode(new Number(), value, _calculate_index));
			} else {
				// constants
				switch (value) {
				case 10:;
				}
			}
			if (Error::error_thrown()) {
				_cursor_index = _calculate_index;
				return new Number();
			}
		}
	}
	if (_number_value_cnt != 0) calculation.push_back(CalculateNode(get_number(), 95, _calculate_index + (_number_value_cnt & 0b00111111)));

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
		if (op != 95) {
			if (!operation) operation = true;
			else {
				if (op == 70 || op == 116) {
					negative = !negative;
					calculation.erase(calculation.begin() + i--);
				} else if (op != 69) {
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
		if (calculation.at(i).operation != 95) {
			operation = true;
		} else {
			if (!operation) {
				// automatic brackets
				// if (i > 1 && calculation.at(i - 2).operation == 72) {
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i + 1, new EquationNode{ 75 });
				//	equation.insert(equation.begin() + calculation.at(i - 1).equation_index + add_i++, new EquationNode{ 74 });
				//}
				// if (equation.at(calculation.at(i).equation_index + add_i)->value == 110) {
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i + 1, new EquationNode{ 75 });
				//	equation.insert(equation.begin() + calculation.at(i).equation_index + add_i++, new EquationNode{ 74 });
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
		if (calculation.at(i).operation != 95) {
			if (calculation.at(i).operation == 71) calculation.at(i - 1).value->multiply(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == 72) calculation.at(i - 1).value->divide(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == 130) calculation.at(i - 1).value->mod(calculation.at(i + 1).value);
			else continue;
			calculation.erase(calculation.begin() + i);
			calculation.erase(calculation.begin() + i--);
		}
	}

	// addition and subtraction
	for (uint32_t i = 0; i < calculation.size(); i++) {
		if (calculation.at(i).operation != 95) {
			if (calculation.at(i).operation == 69) calculation.at(i - 1).value->add(calculation.at(i + 1).value);
			else if (calculation.at(i).operation == 70) calculation.at(i - 1).value->subtract(calculation.at(i + 1).value);
			else continue;
			calculation.erase(calculation.begin() + i);
			calculation.erase(calculation.begin() + i--);
		}
	}

	// logic operators

	return calculation.at(0).value;
}

void Equation::clear_number()
{
	_number_val = 0;
	_number_exp = 0;
	_number_state = 0;
	_number_value_cnt = 0;
}

bool Equation::add_digit(const KEY digit)
{
	// TODO: numbers with more than 18 digits
	if (_number_state & 0b00100000) {
		if (digit < 10) {
			_number_exp--;
			_number_state++;
			_number_val = _number_val * 10 + digit;
		} else if (digit == 238) _number_state ^= 0b00100000;
		else Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
	} else {
		if (_number_state & 0b00011111) return false;
		if (digit < 10) { // key is digit
			if (_number_state & 0b10000000) {
				_number_exp = _number_exp * 10 + digit;
				_number_value_cnt |= 0b10000000;
			} else {
				if (_number_state & 0b01000000) _number_exp--;
				_number_val = _number_val * 10 + digit;
				_number_value_cnt |= 0b01000000;
			}
			//} else if (digit == 69) { // key is +
			//	if (!(_number_state & 0b10000000)) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			//} else if (digit == 70) { // key is -
			//	if (_number_state & 0b10000000) _exp *= -1;
			//	else Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		} else if (digit == 82) { // key is comma
			if (_number_state & 0b11000000) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			_number_state |= 0b01000000;
			//_number_value_cnt |= 0b01000000;
		} else if (digit == 127) { // key is exp
			if (_number_state & 0b10000000) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			_number_state |= 0b10000000;
		} else if (digit == 133) { // key is periodic
			if (!(_number_state & 0b01000000) || _number_state & 0b10000000) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			else _number_state |= 0b00100000;
		} else {
			return false;
		}
	}

	_number_value_cnt++;
	if ((_number_value_cnt & 0b00111111) == 0b00111111) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);

	return true;
}

Number* Equation::get_number()
{
	Number* num;
	if (_number_state & 0b00100000 || _number_value_cnt == 0) {
		Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		num = new Number();
	} else if (_number_state & 0b00011111) {
		num = new Number(_number_val, _number_exp, _number_state & 0b00011111);
	} else {
		num = new Number(_number_val, _number_exp);
	}

	clear_number();
	return num;
}