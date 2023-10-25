#include "calculator/Equation.h"

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

Bitset2D Equation::get_rendered_equation()
{
	// change _show_cursor every 500ms
	if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time += 500000;
		_show_cursor = !_show_cursor;
	}

	return _show_cursor ? _rendered_equation_cursor : _rendered_equation;
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
		_rendered_equation_cursor.set(cursor_data.x, cursor_data.y, Bitset2D(2, cursor_data.size, true), true);
	}
}

Bitset2D Equation::render_equation_part(const std::vector<EquationNode*>& equation, FONT& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint32_t& i, bool stop_on_closed_bracket)
{
	uint8_t font_height = table.at(0).height();
	uint32_t y_origin = 0;
	Bitset2D equation_part(1, font_height, false);
	CursorPositionData cursor_data_new = { 0, 0, 0 };
	render_index.push_back(i);

	if (equation.size() == 0) {
		if (render_index == _cursor_index) cursor_data = { 0, 0, font_height };
		y_origin_ref = 0;
		return table.at(Chars::KEY_MAP.at("empty"));
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
			uint32_t new_y_origin;
			render_index.pop_back();
			symbol_matrix = render_equation_part(equation, table, render_index, cursor_data_subequation, new_y_origin, ++i, true);
			symbol_matrix.erase_x(symbol_matrix.width() - 1);
			if (cursor_data_subequation.size != 0) {
				cursor_data_new = cursor_data_subequation;
				cursor_data_new.x += equation_part.width() + 5;
				cursor_data_new.y -= new_y_origin;
			}

			// add opening bracket
			render_index.push_back(i);
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

		else if (value == 106) {
		}

		else if (value == 107) {
		}


		// fraction
		else if (value == 110) {
			// render top and bottom
			uint8_t fraction_line_height = (font_height == 9) ? 3 : 2;
			uint32_t new_y_origin;
			uint8_t subequation_cursor_index = -1;
			auto bottom = render_subequation(current_symbol->children, 0, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), 0);
			auto top = render_subequation(current_symbol->children, 1, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, new_y_origin, subequation_cursor_index, equation_part.width(), fraction_line_height + 3);
			if (subequation_cursor_index == 0) cursor_data_new.y += fraction_line_height - bottom.height();

			// extend the top and bottom to the same width
			int32_t diff = top.width() - bottom.width();
			if (diff > 0) {
				bottom.extend_right(diff / 2, false);
				bottom.extend_left((diff + 1) / 2, false);
				if (subequation_cursor_index == 0) cursor_data_new.x += (diff + 1) / 2;
			} else if (diff < 0) {
				top.extend_right(-diff / 2, false);
				top.extend_left((-diff + 1) / 2, false);
				if (subequation_cursor_index == 1) cursor_data_new.x += (-diff + 1) / 2;
			}
			// combine top and bottom with a fraction line
			for (uint32_t i = 0; i < bottom.width(); i++) {
				DynamicBitset column = bottom[i];
				column.push_back(false);
				column.push_back(true);
				column.push_back(false);
				column.insert(column.size(), top[i]);
				symbol_matrix.push_back(column);
			}

			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, bottom.height() - fraction_line_height);
		}

		else if (value == 111) {
		}

		// *10^n
		else if (value == 127) {
			symbol_matrix = table.at(Chars::KEY_MAP.at("*10^n"));
			symbol_matrix.extend_right(1, false);
			symbol_matrix.extend_right(table.at(Chars::KEY_MAP.at("10^n")));
			extend_bitset_left_and_match_y_origin(equation_part, y_origin, symbol_matrix, 0);
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

	cursor_data_new.y += y_origin;
	y_origin_ref = y_origin;
	if (cursor_data_new.size != 0) cursor_data = cursor_data_new;
	return equation_part;
}

void Equation::extend_bitset_left_and_match_y_origin(Bitset2D& bitset, uint32_t& y_origin, Bitset2D& bitset_new, uint32_t y_origin_new)
{
	if (y_origin < y_origin_new) {
		bitset.extend_up(y_origin_new - y_origin, false);
		y_origin = y_origin_new;
	} else bitset_new.extend_up(y_origin - y_origin_new, false);
	if (bitset.height() < bitset_new.height()) bitset.extend_down(bitset_new.height() - bitset.height(), false);
	else bitset_new.extend_down(bitset.height() - bitset_new.height(), false);
	bitset.extend_right(bitset_new);
}

Bitset2D Equation::render_subequation(const std::vector<EquationNode*>& equation, uint8_t child_index, FONT& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint8_t& child_index_cursor, uint32_t cursor_offset_x, uint32_t cursor_offset_y)
{
	uint32_t new_start_index = 0;
	CursorPositionData cursor_data_new = { 0, 0, 0 };
	render_index.push_back(child_index);
	auto rendered = render_equation_part(equation.at(child_index)->children, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_new, y_origin_ref, new_start_index);
	if (cursor_data_new.size != 0) {
		cursor_data = cursor_data_new;
		cursor_data.x += cursor_offset_x;
		cursor_data.y += cursor_offset_y;
		child_index_cursor = child_index;
	}
	render_index.pop_back();
	return rendered;
}

double Equation::calculate_equation(const std::vector<double> variables, Error& error)
{
	uint32_t i = 0;
	CalculateNode calculation = calculate_equation_part(_equation_root->children, error, std::vector<uint32_t>(), i);
	return calculation.value;
}

Equation::CalculateNode Equation::calculate_equation_part(const std::vector<EquationNode*>& equation, Error& error, std::vector<uint32_t> calculate_index, uint32_t& i, bool stop_on_closed_bracket)
{
	calculate_index.push_back(i);
	// equation is empty
	if (equation.size() == 0) {
		_cursor_index = std::vector<uint32_t>{ 0 };
		error = Error::SYNTAX_ERROR;
		render_equation();
		return CalculateNode();
	}

	// parse the equation to a 1D vector of numbers and operations
	std::vector<CalculateNode> calculation;
	bool numExpected = true;
	std::string num;
	for (; i < equation.size(); i++) {
		calculate_index.back() = i;
		if (equation[i]->children.size() == 0) {
			uint8_t value = equation[i]->value;
			if (value < 10) {
				num.push_back(value + 48);
			} else if (value == Chars::KEY_MAP.at(",")) {
				num.push_back('.');
			} else if (value == Chars::KEY_MAP.at("*10^n")) {
				num.push_back('e');
			} else {
				if (num != "") {
					calculation.push_back(CalculateNode{ std::stod(num), 95 });
					num = "";
				}

				if (std::count(_single_bracket_open_keys.begin(), _single_bracket_open_keys.end(), value) != 0) {
					Error err;
					calculate_index.pop_back();
					calculation.push_back(calculate_equation_part(equation, err, calculate_index, ++i, true));
					calculate_index.push_back(i);
				} else if (value == Chars::KEY_MAP.at(")")) {
					if (stop_on_closed_bracket) {
						break;
					} else {
						_cursor_index = calculate_index;
						error = Error::SYNTAX_ERROR;
						render_equation();
						return CalculateNode();
					}
				} else if (std::count(_allowed_calculate_operations.begin(), _allowed_calculate_operations.end(), value) || (value > 189 && value < 236)) {
					calculation.push_back(CalculateNode(0, value));
				} else {
					switch (value) {
					case 10:;
					}
				}
			}
		} else {
			Error err;
			std::vector<CalculateNode> subEquations;
			for (EquationNode* node : equation[i]->children) {
				uint32_t new_i = 0;
				subEquations.push_back(calculate_equation_part(node->children, err, calculate_index, new_i));
				switch (err) {
				case Error::MATH_ERROR:;
				case Error::PUFFER_ERROR:;
				case Error::SYNTAX_ERROR:;
				case Error::ARGUMENT_ERROR:;
				case Error::STORAGE_ERROR:;
				case Error::TIME_ERROR:;
				case Error::FINE:;
				}
			}
			uint8_t value = equation[i]->value;
			if (value == 110) {
				calculation.push_back(CalculateNode(subEquations[0].value / subEquations[1].value, 95));
			} else if (calculation.back().value != 95) {
				if (value == 113) calculation.back() = CalculateNode(pow(calculation.back().value, subEquations[0].value), 95);
				else if (value == 85) calculation.back() = CalculateNode(tgamma(calculation.back().value - 1), 95);
				else if (value == 98) calculation.back() = CalculateNode(calculation.back().value / 100, 95);
			} else {
				_cursor_index = calculate_index;
				error = Error::SYNTAX_ERROR;
				render_equation();
				return CalculateNode();
			}
		}
	}
	if (num != "") {
		calculation.push_back(CalculateNode{ std::stod(num), 95 });
		num = "";
	}

	// handle negative numbers
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
					_cursor_index = calculate_index;
					error = Error::SYNTAX_ERROR;
					return CalculateNode();
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

	return calculation.at(0);
}


void Equation::add_value(uint8_t keypress)
{
	switch (keypress) {
	case 106: add_value_raw(keypress, 1); break;
	case 107: add_value_raw(keypress, 1, false, std::vector<uint8_t>{ 3 }); break;
	case 108: add_value_raw(keypress, 1, false, std::vector<uint8_t>{ 116, 1 }); break;
	case 109: add_value_raw(keypress, 2, true); break;
	case 110: add_value_raw(keypress, 2, true); break;
	case 111: add_value_raw(keypress, 1); break;
	case 112: add_value_raw(keypress, 1, false, std::vector<uint8_t>{ 2 }); break;
	case 113: add_value_raw(keypress, 1); break;
	case 131: add_value_raw(keypress, 3, true); break;
	case 132: add_value_raw(keypress, 2, true); break;
	case 133: add_value_raw(keypress, 1); break; // condition
	case 134: add_value_raw(keypress, 2, true); break;
	case 135: add_value_raw(keypress, 1); break;
	case 136: add_value_raw(keypress, 1); break;
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
	if (_equation_root->children.size() == 0) return;

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
		if (_cursor_index.back() == 0 && modify_parent->children.size() > _cursor_index[i - 1] + 1) {
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
