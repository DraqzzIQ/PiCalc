#include "calculator/Equation.h"

const std::vector<uint8_t> Equation::_allowed_calculate_operations = { 69, 70, 71, 72, 74, 75, 85, 98, 114, 115, 116, 118, 119, 120, 130, 138, 139, 140, 152, 153, 154, 159, 162, 163, 164 };
const std::vector<uint8_t> Equation::_single_bracket_open_keys = { 74, 114, 115, 118, 119, 120, 138, 139, 140, 152, 153, 154, 160, 161, 162, 163, 164, 190, 191, 192, 193, 194, 195 };
const std::vector<uint8_t> Equation::_values_before_exponent = { 75, 85, 102, 106, 109, 110, 111, 127, 128, 131, 155, 156, 165, 186, 187, 188 };

Equation::Equation()
{
	_equation_root = new EquationNode();
	_cursor_index = std::vector<uint32_t>{ 0 };
	render_equation();
}

Equation::~Equation()
{
	delete _equation_root;
}

Bitset2D Equation::get_rendered_equation(bool complete)
{
	// change _show_cursor every 500ms
	if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time += 500000;
		_show_cursor = !_show_cursor;
	}

	if (complete) return _show_cursor ? _rendered_equation_cursor : _rendered_equation;
	else
}

void Equation::render_equation()
{
	// show the cursor and reset the blink timer
	_last_blink_time = Utils::us_since_boot();
	_show_cursor = true;

	// show nothing if the equation is empty
	if (_equation_root->children.size() == 0) {
		_rendered_equation = Bitset2D();
		_rendered_equation_cursor = Bitset2D(2, 9, true);
	} else {
		// render the equation with and without the cursor
		CursorPositionData cursor_data;
		uint32_t y_origin = 0;
		uint32_t start_index = 0;
		_rendered_equation = render_equation_part(_equation_root->children, Graphics::SYMBOLS_9_HIGH, std::vector<uint32_t>(), cursor_data, y_origin, start_index);
		_rendered_equation_cursor = _rendered_equation;
		cursor_data.y += y_origin;
		_rendered_equation_cursor.set(cursor_data.x, cursor_data.y, Bitset2D(2, cursor_data.size, true), true);
	}
}

Bitset2D Equation::render_equation_part(const std::vector<EquationNode*>& equation, FONT& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint32_t& i, bool stop_on_closed_bracket)
{
	uint8_t font_height = table.at(0).height();
	int32_t y_origin = 0;
	Bitset2D equation_part(1, font_height, false);
	CursorPositionData cursor_data_new = { 0, 0, 0 };
	render_index.push_back(i);

	if (equation.size() == 0) {
		if (render_index == _cursor_index) cursor_data = { 0, 0, font_height };
		y_origin_ref = 0;
		equation_part.extend_left(table.at(Chars::KEY_MAP.at("empty")));
		equation_part.extend_left(1, false);
		return equation_part;
	}
	for (; i < equation.size(); i++) {
		EquationNode* current_symbol = equation.at(i);
		uint8_t value = current_symbol->value;
		Bitset2D symbol_matrix = Bitset2D();
		render_index.back() = i;
		if (render_index == _cursor_index) cursor_data_new = { equation_part.width() - 1, 0, font_height };

		// any symbol with an open bracket at the end
		if (std::count(_single_bracket_open_keys.begin(), _single_bracket_open_keys.end(), value) != 0 && value != 74) {
			// only render the text before the bracket, then change the value to 74 for the other case to render the actual bracket
			std::vector<uint8_t> keys = Graphics::key_text.at(value);
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
			CursorPositionData cursor_data_subequation = { 0, 0, 0 };
			uint32_t new_y_origin = 0;
			if (i != equation.size() - 1) {
				render_index.pop_back();
				symbol_matrix = render_equation_part(equation, table, render_index, cursor_data_subequation, new_y_origin, ++i, true);
				symbol_matrix.erase_x(symbol_matrix.width() - 1);
				if (cursor_data_subequation.size != 0) {
					cursor_data_new = cursor_data_subequation;
					cursor_data_new.x += equation_part.width() + 5;
				}
				render_index.push_back(i);
			} else symbol_matrix = Bitset2D(0, font_height, false);

			// add opening bracket
			if (symbol_matrix.height() == 6) symbol_matrix.extend_left(Graphics::SYMBOLS_6_HIGH.at(74));
			else {
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
			}

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, new_y_origin);
		}

		// closed bracket
		else if (value == 75) {
			if (equation_part.height() == 6) equation_part.extend_right(Graphics::SYMBOLS_6_HIGH.at(75));
			else {
				DynamicBitset bracket_raw(equation_part.height() - 4, true);
				bracket_raw.extend_left(2, false);
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
			if (stop_on_closed_bracket) {
				break;
			}
		}

		// Abs
		else if (value == 106) {
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;
			symbol_matrix = render_subequation(current_symbol->children, 0, table, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width() + 5, 0);
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

			uint8_t subequation_cursor_index = -1;
			uint32_t new_y_origin;

			// render the subequation
			symbol_matrix = render_subequation(current_symbol->children, 0, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			if (subequation_cursor_index == 0) cursor_data_new.y += new_y_origin + 5;
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, -5);

			symbol_matrix = render_subequation(current_symbol->children, 1, table, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width() + 5, 0);

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
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;
			bool mixed = false;
			if (value == 131) {
				mixed = true;
				auto front = render_subequation(current_symbol->children, 0, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), fraction_line_height - 2);
				extend_bitset_left_and_match_y_origin(equation_part, y_origin, front, -fraction_line_height + 2);
			}
			auto top = render_subequation(current_symbol->children, mixed ? 1 : 0, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			if (subequation_cursor_index == (mixed ? 1 : 0)) cursor_data_new.y += new_y_origin - top.height() + fraction_line_height;
			auto bottom = render_subequation(current_symbol->children, mixed ? 2 : 1, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			if (subequation_cursor_index == (mixed ? 2 : 1)) cursor_data_new.y += new_y_origin + fraction_line_height + 3;

			// extend the top and bottom to the same width
			int32_t diff = bottom.width() - top.width();
			if (diff > 0) {
				top.extend_right(diff / 2, false);
				top.extend_left((diff + 1) / 2, false);
				if (subequation_cursor_index == (mixed ? 1 : 0)) cursor_data_new.x += (diff + 1) / 2;
			} else if (diff < 0) {
				bottom.extend_right(-diff / 2, false);
				bottom.extend_left((-diff + 1) / 2, false);
				if (subequation_cursor_index == (mixed ? 2 : 1)) cursor_data_new.x += (-diff + 1) / 2;
			}
			// combine top and bottom with a fraction line
			for (uint32_t i = 0; i < top.width(); i++) {
				DynamicBitset column = top[i];
				column.push_back(false);
				column.push_back(true);
				column.push_back(false);
				column.insert(column.size(), bottom[i]);
				symbol_matrix.push_back(column);
			}

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, top.height() - fraction_line_height);
		}

		// root2
		else if (value == 111) {
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;
			symbol_matrix = render_subequation(current_symbol->children, 0, table, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width() + 4, 0);
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
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;

			if (value == 135) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(135), 0);
			else if (value == 136) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(165), 0);
			else {
				if (i == 0 || !(equation.at(i - 1)->value < 69 || std::count(_values_before_exponent.begin(), _values_before_exponent.end(), equation.at(i - 1)->value) != 0)) extend_bitset_left_and_match_y_origin(equation_part, y_origin, table.at(Chars::KEY_MAP.at("empty")), 0);
				else equation_part.pop_back_x();
			}
			symbol_matrix = render_subequation(current_symbol->children, 0, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			if (subequation_cursor_index == 0) cursor_data_new.y += new_y_origin - symbol_matrix.height() + 4;
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, symbol_matrix.height() - 4);
		}

		// *10^n
		else if (value == 127) {
			symbol_matrix = table.at(Chars::KEY_MAP.at("*10^n"));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table.at(Chars::KEY_MAP.at("10^n")));
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// periodic
		else if (value == 133) {
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;
			symbol_matrix = render_subequation(current_symbol->children, 0, table, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			symbol_matrix.extend_up(1, false);
			symbol_matrix.extend_up(1, true);
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 2);
		}

		// rootn
		else if (value == 134) {
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;
			symbol_matrix = render_subequation(current_symbol->children, 0, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			if (subequation_cursor_index == 0) cursor_data_new.y += new_y_origin - symbol_matrix.height() + 2;
			symbol_matrix.extend_down(7, false);
			symbol_matrix.set_bit(symbol_matrix.width() - 2, symbol_matrix.height() - 3, true);
			symbol_matrix.set_bit(symbol_matrix.width() - 1, symbol_matrix.height() - 2, true);

			Bitset2D radicant = render_subequation(current_symbol->children, 1, table, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width() + symbol_matrix.width() + 2, 0);
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

		// any other symbol
		else {
			if (table.count(value) != 0) symbol_matrix = table.at(value);
			else symbol_matrix = table.at(Chars::KEY_MAP.at("?"));
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
		}

		// add space after the symbol
		equation_part.push_back(DynamicBitset(equation_part.height(), false));
	}
	// special case: cursor at the end of the equation
	render_index.back()++;
	if (render_index == _cursor_index) cursor_data_new = { equation_part.width() - 1, 0, font_height };

	// cursor_data_new.y += y_origin;
	y_origin_ref = y_origin;
	if (cursor_data_new.size != 0) cursor_data = cursor_data_new;
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

Bitset2D Equation::render_subequation(const std::vector<EquationNode*>& equation, uint8_t child_index, FONT& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint8_t& child_index_cursor, int32_t cursor_offset_x, int32_t cursor_offset_y)
{
	uint32_t new_start_index = 0;
	CursorPositionData cursor_data_new = { 0, 0, 0 };
	render_index.push_back(child_index);
	auto rendered = render_equation_part(equation.at(child_index)->children, table, render_index, cursor_data_new, y_origin_ref, new_start_index);
	if (cursor_data_new.size != 0) {
		cursor_data = cursor_data_new;
		cursor_data.x += cursor_offset_x;
		cursor_data.y += cursor_offset_y;
		child_index_cursor = child_index;
	}
	render_index.pop_back();
	return rendered;
}

Number Equation::calculate_equation(const std::vector<double> variables)
{
	uint32_t i = 0;
	Number res = calculate_equation_part(_equation_root->children, std::vector<uint32_t>(), i);
	if (Error::error_thrown()) return Number();
	render_equation();
	return res;
}

Number Equation::calculate_equation_part(std::vector<EquationNode*>& equation, std::vector<uint32_t> calculate_index, uint32_t& i, bool stop_on_closed_bracket)
{
	calculate_index.push_back(i);

	// equation is empty
	if (equation.size() == 0) {
		Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		_cursor_index = calculate_index;
		return Number();
	}

	// parse the equation to a 1D vector of numbers and operations
	std::vector<CalculateNode> calculation;
	bool numExpected = true;
	Number number = Number();
	for (; i < equation.size(); i++) {
		calculate_index.back() = i;
		uint8_t value = equation[i]->value;

		if (value == 133) {
			number.add_digit(133);
			for (uint32_t j = 0; j < equation[i]->children.size(); j++) {
				number.add_digit(equation[i]->children[0]->children[j]->value);
			}
			number.add_digit(133);
		} else if (!number.add_digit(value)) {
			if (uint16_t length = number.finalize()) calculation.push_back(CalculateNode(number, 95, i - length));

			if (equation[i]->children.size() != 0) {
				std::vector<Number> subEquations;
				for (EquationNode* node : equation[i]->children) {
					uint32_t new_i = 0;
					subEquations.push_back(calculate_equation_part(node->children, calculate_index, new_i));
				}
				switch (value) {
				case 95: Error::throw_error(Error::ErrorType::SYNTAX_ERROR); break;
				case 106: calculation.push_back(CalculateNode(subEquations[0].abs(), 95, i)); break;
				case 109: calculation.push_back(CalculateNode(subEquations[0].log(subEquations[1]), 95, i)); break;
				case 110: calculation.push_back(CalculateNode(subEquations[0] / subEquations[1], 95, i)); break;
				case 111: calculation.push_back(CalculateNode(subEquations[0].root(2), 95, i)); break;
				case 131: calculation.push_back(CalculateNode(subEquations[0] + (subEquations[1] / subEquations[2]), 95, i)); break;
				case 134: calculation.push_back(CalculateNode(subEquations[1].root(subEquations[0]), 95, i)); break;
				case 135: calculation.push_back(CalculateNode(Number(10).pow(subEquations[0]), 95, i)); break;
				case 136: calculation.push_back(CalculateNode(Number::euler.pow(subEquations[0]), 95, i)); break;
				default:
					if (calculation.size() == 0 || calculation.back().operation != 95) {
						Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
					}
					switch (value) {
					case 113: calculation.back().value.pow(subEquations[0]); break;
					case 85: calculation.back().value.factorial(); break;
					case 98: calculation.back().value /= 100; break;
					}
				}
			} else if (std::count(_single_bracket_open_keys.begin(), _single_bracket_open_keys.end(), value) != 0) {
				calculate_index.pop_back();
				Number result = calculate_equation_part(equation, calculate_index, ++i, true);
				Number result2;
				if (value == 152 || value == 153 || value == 160 || value == 161 || value == 164) result2 = calculate_equation_part(equation, calculate_index, ++i, true);
				calculate_index.push_back(i);
				switch (value) {
				case 74: calculation.push_back(CalculateNode(result, 95, i)); break;
				case 114: calculation.push_back(CalculateNode(result.log(), 95, i)); break;
				case 115: calculation.push_back(CalculateNode(result.ln(), 95, i)); break;
				case 118: calculation.push_back(CalculateNode(result.sin(), 95, i)); break;
				case 119: calculation.push_back(CalculateNode(result.cos(), 95, i)); break;
				case 120: calculation.push_back(CalculateNode(result.tan(), 95, i)); break;
				case 138: calculation.push_back(CalculateNode(result.asin(), 95, i)); break;
				case 139: calculation.push_back(CalculateNode(result.acos(), 95, i)); break;
				case 140: calculation.push_back(CalculateNode(result.atan(), 95, i)); break;
				case 152: calculation.push_back(CalculateNode(Number::pol(result, result2), 95, i)); break;
				case 153: calculation.push_back(CalculateNode(Number::rec(result, result2), 95, i)); break;
				case 154: calculation.push_back(CalculateNode(result.round(), 95, i)); break;
				case 160: calculation.push_back(CalculateNode(Number::gcd(result, result2), 95, i)); break;
				case 161: calculation.push_back(CalculateNode(Number::lcm(result, result2), 95, i)); break;
				case 162: calculation.push_back(CalculateNode(result.to_int(), 95, i)); break;
				case 163: calculation.push_back(CalculateNode(result.floor(), 95, i)); break;
				case 164: calculation.push_back(CalculateNode(Number::ran_int(result, result2), 95, i)); break;
				case 190: calculation.push_back(CalculateNode(result.sinh(), 95, i)); break;
				case 191: calculation.push_back(CalculateNode(result.cosh(), 95, i)); break;
				case 192: calculation.push_back(CalculateNode(result.tanh(), 95, i)); break;
				case 193: calculation.push_back(CalculateNode(result.asinh(), 95, i)); break;
				case 194: calculation.push_back(CalculateNode(result.acosh(), 95, i)); break;
				case 195: calculation.push_back(CalculateNode(result.atanh(), 95, i)); break;
				}
			} else if (value == 75 || value == 83) {
				if (stop_on_closed_bracket) break;
				else Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			} else if (std::count(_allowed_calculate_operations.begin(), _allowed_calculate_operations.end(), value) || (value > 189 && value < 236)) {
				calculation.push_back(CalculateNode(Number(), value, i));
			} else {
				// constants
				switch (value) {
				case 10:;
				}
			}
			if (Error::error_thrown()) {
				_cursor_index = calculate_index;
				return Number();
			}
		}
	}
	if (uint16_t length = number.finalize()) calculation.push_back(CalculateNode(number, 95, i - length));

	// handle negative numbers
	uint8_t add_i = 0;
	bool negative = false;
	bool operation = true;
	for (uint32_t j = 0; j < calculation.size(); j++) {
		calculate_index.back() = j;
		if (calculation.at(j).operation != 95) {
			if (!operation) operation = true;
			else {
				if (calculation.at(j).operation == 70 || calculation.at(j).operation == 116) {
					negative = !negative;
					calculation.erase(calculation.begin() + j--);
				} else if (calculation.at(j).operation != 69) {
					Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
					_cursor_index = calculate_index;
					return Number();
				}
			}
		} else {
			if (negative) calculation.at(j).value *= -1;
			negative = false;
			operation = false;
		}
	}

	// metric conversion

	// multiplication without sign
	operation = true;
	for (uint32_t j = 0; j < calculation.size(); j++) {
		calculate_index.back() = j;
		if (calculation.at(j).operation != 95) {
			operation = true;
		} else {
			if (!operation) {
				if (j > 1 && calculation.at(j - 2).operation == 72) {
					equation.insert(equation.begin() + calculation.at(j).equation_index + add_i + 1, new EquationNode{ 75 });
					equation.insert(equation.begin() + calculation.at(j - 1).equation_index + add_i++, new EquationNode{ 74 });
				}
				if (equation.at(calculation.at(j).equation_index + add_i)->value == 110) {
					equation.insert(equation.begin() + calculation.at(j).equation_index + add_i + 1, new EquationNode{ 75 });
					equation.insert(equation.begin() + calculation.at(j).equation_index + add_i++, new EquationNode{ 74 });
				}
				calculation.at(j - 1).value *= calculation.at(j).value;
				calculation.erase(calculation.begin() + j--);
			}
			operation = false;
		}
	}

	// permutation and combination

	// multiplication and division
	for (uint32_t j = 0; j < calculation.size(); j++) {
		calculate_index.back() = j;
		if (calculation.at(j).operation != 95) {
			if (calculation.at(j).operation == 71) calculation.at(j - 1).value *= calculation.at(j + 1).value;
			else if (calculation.at(j).operation == 72) calculation.at(j - 1).value /= calculation.at(j + 1).value;
			else if (calculation.at(j).operation == 130) calculation.at(j - 1).value %= calculation.at(j + 1).value;
			else continue;
			calculation.erase(calculation.begin() + j);
			calculation.erase(calculation.begin() + j--);
		}
	}

	// addition and subtraction
	for (uint32_t j = 0; j < calculation.size(); j++) {
		calculate_index.back() = j;
		if (calculation.at(j).operation != 95) {
			if (calculation.at(j).operation == 69) calculation.at(j - 1).value += calculation.at(j + 1).value;
			else if (calculation.at(j).operation == 70) calculation.at(j - 1).value -= calculation.at(j + 1).value;
			else continue;
			calculation.erase(calculation.begin() + j);
			calculation.erase(calculation.begin() + j--);
		}
	}

	// logic operators

	return calculation.at(0).value;
}


void Equation::add_value(uint8_t keypress)
{
	// TODO: restrictions
	switch (keypress) {
	case 106: add_value_raw(106, 1); break;
	case 107: add_value_raw(113, 1, false, std::vector<uint8_t>{ 3 }); break;
	case 108: add_value_raw(113, 1, false, std::vector<uint8_t>{ 116, 1 }); break;
	case 109: add_value_raw(109, 2, true); break;
	case 110: add_value_raw(110, 2, true); break;
	case 111: add_value_raw(111, 1); break;
	case 112: add_value_raw(113, 1, false, std::vector<uint8_t>{ 2 }); break;
	case 113: add_value_raw(113, 1); break;
	case 131: add_value_raw(131, 3, true); break;
	case 132: add_value_raw(134, 2, true); break;
	case 133: add_value_raw(133, 1); break; // condition
	case 134: add_value_raw(134, 2, true); break;
	case 135: add_value_raw(135, 1); break;
	case 136: add_value_raw(136, 1); break;
	default: add_value_raw(keypress, 0); break;
	}

	render_equation();
}

void Equation::add_value_raw(uint8_t value, uint8_t child_cnt, bool add_value_to_first_child, std::vector<uint8_t> first_child)
{
	EquationNode* modify;
	modify = _equation_root;
	for (size_t i = 0; i < _cursor_index.size() - 1; i++) modify = modify->children.at(_cursor_index[i]);

	if (child_cnt != 0) {
		if (add_value_to_first_child) {
			EquationNode* container = new EquationNode();
			container->value = value;
			container->children = std::vector<EquationNode*>(child_cnt);
			for (uint8_t i = 0; i < child_cnt; i++) {
				container->children.at(i) = new EquationNode();
				container->children.at(i)->children = std::vector<EquationNode*>(0);
			}

			uint32_t end = _cursor_index.back();
			while (_cursor_index.back() != 0) {
				uint8_t val = modify->children.at(_cursor_index.back() - 1)->value;
				if (!(val < 10 || val == 82 || val == 127 || modify->children.at(_cursor_index.back() - 1)->children.size() != 0)) break;
				_cursor_index.back()--;
			}
			if (end != _cursor_index.back()) {
				auto ptrBegin = modify->children.begin() + _cursor_index.back();
				auto ptrEnd = modify->children.begin() + end;
				container->children.at(0)->children = { ptrBegin, ptrEnd };
				modify->children.erase(ptrBegin, ptrEnd);
				auto ptr = modify->children.begin() + _cursor_index.back();
				modify->children.insert(ptr, container);
				if (child_cnt > 1) {
					_cursor_index.push_back(1);
					_cursor_index.push_back(0);
				} else {
					_cursor_index.back()++;
				}
			} else {
				auto ptr = modify->children.begin() + _cursor_index.back();
				modify->children.insert(ptr, container);
				_cursor_index.push_back(0);
				_cursor_index.push_back(0);
			}
		} else {
			EquationNode* container = new EquationNode();
			container->value = value;
			container->children = std::vector<EquationNode*>(child_cnt);
			for (uint8_t i = 0; i < child_cnt; i++) {
				container->children.at(i) = new EquationNode();
				container->children.at(i)->children = std::vector<EquationNode*>(0);
			}
			for (uint8_t i = 0; i < first_child.size(); i++) {
				container->children.at(0)->children.push_back(new EquationNode{ first_child.at(i), std::vector<EquationNode*>() });
			}
			auto ptr = modify->children.begin() + _cursor_index.back();
			modify->children.insert(ptr, container);
			_cursor_index.push_back(0);
			_cursor_index.push_back(0);
		}
	} else {
		EquationNode* container = new EquationNode();
		container->value = value;
		std::vector<EquationNode*>::iterator ptr = modify->children.begin();
		advance(ptr, _cursor_index.back());
		modify->children.insert(ptr, container);
		_cursor_index.back() += 1;
	}
}

void Equation::move_cursor_left()
{
	EquationNode* modify = _equation_root;
	EquationNode* modify_parent = _equation_root;
	uint32_t i = 0;
	for (; i + 1 < _cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children.at(_cursor_index[i]);
	}
	if (_cursor_index.back() != 0) {
		if (modify->children.at(_cursor_index.back() - 1)->children.size() != 0) {
			_cursor_index.back() -= 1;
			std::vector<EquationNode*> modify_child = modify->children.at(_cursor_index.back())->children;
			_cursor_index.push_back(modify_child.size() - 1);
			_cursor_index.push_back(modify_child.at(_cursor_index.back())->children.size());
		} else {
			_cursor_index.back() -= 1;
		}
	} else if (_cursor_index.size() == 1) {
		_cursor_index.back() = modify->children.size();
	} else if (_cursor_index[i - 1] != 0) {
		_cursor_index[i - 1] -= 1;
		_cursor_index[i] = modify_parent->children.at(_cursor_index[i - 1])->children.size();
	} else {
		_cursor_index.pop_back();
		_cursor_index.pop_back();
	}
	render_equation();
}

void Equation::move_cursor_right()
{
	EquationNode* modify = _equation_root;
	EquationNode* modify_parent = _equation_root;
	uint32_t i = 0;
	for (; i + 1 < _cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children.at(_cursor_index[i]);
	}
	if (modify->children.size() > _cursor_index.back()) {
		if (modify->children.at(_cursor_index.back())->children.size() != 0) {
			_cursor_index.push_back(0);
			_cursor_index.push_back(0);
		} else {
			_cursor_index.back() += 1;
		}
	} else if (_cursor_index.size() == 1) {
		_cursor_index.back() = 0;
	} else if (modify_parent->children.size() > _cursor_index[i - 1] + 1) {
		_cursor_index[i - 1] += 1;
		_cursor_index[i] = 0;
	} else {
		_cursor_index.pop_back();
		_cursor_index.pop_back();
		_cursor_index.back() += 1;
	}
	render_equation();
}

void Equation::move_cursor_up()
{
	EquationNode* modify = _equation_root;
	for (int i = 0; i + 2 < _cursor_index.size(); i++) modify = modify->children.at(_cursor_index[i]);

	if (modify->value == 110 && _cursor_index[_cursor_index.size() - 2] == 1) {
		_cursor_index[_cursor_index.size() - 2] = 0;
		_cursor_index.back() = modify->children.at(0)->children.size();
		render_equation();
	}
}

void Equation::move_cursor_down()
{
	// double fraction: not working
	EquationNode* modify = _equation_root;
	for (int i = 0; i + 2 < _cursor_index.size(); i++) modify = modify->children.at(_cursor_index[i]);

	if (modify->value == 110 && _cursor_index[_cursor_index.size() - 2] == 0) {
		_cursor_index[_cursor_index.size() - 2] = 1;
		_cursor_index.back() = 0;
		render_equation();
	}
}

void Equation::del()
{
	if (_cursor_index == std::vector<uint32_t>{ 0 }) return;

	EquationNode* modify = _equation_root;
	EquationNode* modify_parent = _equation_root;
	uint32_t i = 0;
	for (; i + 1 < _cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children.at(_cursor_index[i]);
	}

	if (_cursor_index.back() != 0 && modify->children.at(_cursor_index.back() - 1)->children.size() == 0) {
		modify->children.erase(modify->children.begin() + _cursor_index.back() - 1);
		_cursor_index.back() -= 1;
	} else {
		if (_cursor_index.back() == 0 && _cursor_index[i - 1] == 0) {
			if (_cursor_index.size() == 1) return;
			_cursor_index.pop_back();
			_cursor_index.pop_back();
			EquationNode* modify = _equation_root;
			EquationNode* modify_parent = _equation_root;
			size_t i = 0;
			for (; i < _cursor_index.size(); i++) {
				modify_parent = modify;
				modify = modify->children.at(_cursor_index[i]);
			}
			std::vector<EquationNode*> insert_equation;
			for (uint32_t i = 0; i < modify->children.size(); i++) { insert_equation.insert(insert_equation.end(), modify->children.at(i)->children.begin(), modify->children.at(i)->children.end()); }
			modify_parent->children.erase(modify_parent->children.begin() + _cursor_index.back());
			modify_parent->children.insert(modify_parent->children.begin() + _cursor_index.back(), insert_equation.begin(), insert_equation.end());
		} else {
			move_cursor_left();
		}
	}
	render_equation();
}

void Equation::ac()
{
	delete _equation_root;
	_equation_root = new EquationNode();
	_cursor_index = std::vector<uint32_t>{ 0 };
	render_equation();
}
