#include "Equation.h"

Equation::Equation() {
	_equation_root_raw = new EquationNode();
	_equation_root_raw->children = new std::vector<EquationNode*>(0);
	cursor_index = std::vector<uint32_t>{0};

	equation_changed = true;
}

Equation::~Equation() {
	delete _equation_root_raw;
	delete _equation_root_formatted;
}

Bitset2D Equation::render_equation() {
	if (equation_changed) {
		last_blink_time = Utils::us_since_boot();
		show_cursor = true;
		// the equation is empty
		if (_equation_root_raw->children->size() == 0) {
			rendered_equation = Bitset2D();
			rendered_equation_cursor = Bitset2D(2, 9, true);
		}
		else {
			_equation_root_formatted = format_equation(_equation_root_raw);
			CursorPositionData cursor_data{ 0, 0, 0 };
			uint32_t y_origin = 0;
			rendered_equation = render_equation_part(*_equation_root_formatted->children, Graphics::SYMBOLS_9_HIGH, std::vector<uint32_t>(), cursor_data, y_origin);
			rendered_equation_cursor = rendered_equation;
			rendered_equation_cursor.set(cursor_data.x, cursor_data.y, Bitset2D(2, cursor_data.size, true), true);
		}
		equation_changed = false;
	}

	// change the state of show_cursor every 0.5s
	if (Utils::us_since_boot() > last_blink_time + 500000) {
		last_blink_time += 500000;
		show_cursor = !show_cursor;
	}
	
	return show_cursor ? rendered_equation_cursor : rendered_equation;
}

Bitset2D Equation::render_equation_part(const std::vector<EquationNode*>& equation, const std::map<uint8_t, Bitset2D>& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref) {
	uint8_t font_height = table.at(0).height();
	uint32_t y_origin = 0;
	Bitset2D equation_part(1, font_height, false);
	CursorPositionData cursor_data_new = { 0, 0, 0 };
	render_index.push_back(0);

	if (equation.size() == 0) {
		if (render_index == cursor_index) cursor_data = { 0, 0, font_height };
		y_origin_ref = 0;
		return table.at(Chars::KEY_MAP.at("empty"));
	}
	for (uint32_t i = 0; i < equation.size(); i++) {
		EquationNode* current_symbol = equation.at(i);
		Bitset2D symbol_matrix = Bitset2D();
		render_index.back() = i;
		if (render_index == cursor_index)
			cursor_data_new = { equation_part.width() - 1, 0, font_height };

		if (current_symbol->children == nullptr) {
			if (table.count(*current_symbol->value) != 0) symbol_matrix = table.at(*current_symbol->value);
			else symbol_matrix = table.at(Chars::KEY_MAP.at("?"));
			symbol_matrix.extend_up(y_origin, false);
			symbol_matrix.extend_down(equation_part.height() - symbol_matrix.height(), false);
			equation_part.extend_right(symbol_matrix);
		}
		else {
			render_index.push_back(0);
			if (*current_symbol->value == Chars::KEY_MAP.at("fraction")) {
				int8_t subequation_cursor_index = -1;
				uint32_t new_y_origin;
				CursorPositionData cursor_data_subequation = { 0, 0, 0 };
				render_index.back() = 0;
				auto bottom = render_equation_part(*current_symbol->children->at(0)->children, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_subequation, new_y_origin);
				if (cursor_data_subequation.size != 0) { subequation_cursor_index = 0; cursor_data_new = cursor_data_subequation; }
				cursor_data_subequation = { 0, 0, 0 };
				render_index.back() = 1;
				auto top = render_equation_part(*current_symbol->children->at(1)->children, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_subequation, new_y_origin);
				if (cursor_data_subequation.size != 0) { subequation_cursor_index = 1; cursor_data_new = cursor_data_subequation; }


 				int32_t diff = top.width() - bottom.width();
				if (diff > 0) {
					bottom.extend_right(diff / 2, false);
					bottom.extend_left((diff + 1) / 2, false);
					if (subequation_cursor_index == 0) cursor_data_new.x += (diff + 1) / 2;
				}
				else if (diff < 0) {
					top.extend_right(-diff / 2, false);
					top.extend_left((-diff + 1) / 2, false);
					if (subequation_cursor_index == 1) cursor_data_new.x += (-diff + 1) / 2;
				}

				for (uint32_t i = 0; i < bottom.width(); i++) {
					DynamicBitset column = bottom[i];
					column.push_back(false);
					column.push_back(true);
					column.push_back(false);
					column.insert(column.size(), top[i]);
					symbol_matrix.push_back(column);
				}


				uint8_t fraction_line_height = (font_height == 9) ? 3 : 2;

				if (subequation_cursor_index != -1) {
					cursor_data_new.x += equation_part.width();
					if (subequation_cursor_index == 0)
						cursor_data_new.y += fraction_line_height - bottom.height();
					else if (subequation_cursor_index == 1)
						cursor_data_new.y += fraction_line_height + 3;
				}

				int32_t add_height = y_origin + fraction_line_height - bottom.height();
				if (add_height < 0) { equation_part.extend_up(-add_height, false); y_origin -= add_height; }
				else symbol_matrix.extend_up(add_height, false);
				add_height = symbol_matrix.height() - equation_part.height();
				if (add_height > 0) equation_part.extend_down(add_height, false);
				else symbol_matrix.extend_down(-add_height, false);
				equation_part.extend_right(symbol_matrix);
			}

			else if (*current_symbol->value == Chars::KEY_MAP.at("(")) {
				int8_t subequation_cursor_index = -1;
				CursorPositionData cursor_data_subequation = { 0, 0, 0 };
				uint32_t new_y_origin;
				render_index.back() = 0;
				bool add_close_bracket = *current_symbol->children->at(0)->children->back()->value == 75;
				if (add_close_bracket) current_symbol->children->at(0)->children->pop_back();
				auto inner = render_equation_part(*current_symbol->children->at(0)->children, table, render_index, cursor_data_subequation, new_y_origin);
				if (cursor_data_subequation.size != 0) { subequation_cursor_index = 0; cursor_data_new = cursor_data_subequation; }

				DynamicBitset bracket_raw(inner.height() - 4, true);
				bracket_raw.extend_left(2, false);
				bracket_raw.extend(2, false);

				Bitset2D bracket_left(1, bracket_raw);
				bracket_left.extend_left(1, false);
				bracket_left.extend_right(3, false);
				bracket_left.set_bit(3, 0, true);
				bracket_left.set_bit(2, 1, true);
				bracket_left.set_bit(3, bracket_left.height()-1, true);
				bracket_left.set_bit(2, bracket_left.height()-2, true);

				Bitset2D bracket_right(1, bracket_raw);
				bracket_right.extend_left(3, false);
				bracket_right.extend_right(1, false);
				bracket_right.set_bit(1, 0, true);
				bracket_right.set_bit(2, 1, true);
				bracket_right.set_bit(1, bracket_right.height() - 1, true);
				bracket_right.set_bit(2, bracket_right.height() - 2, true);

				symbol_matrix.extend_right(bracket_left);
				symbol_matrix.extend_right(inner);
				if(add_close_bracket) symbol_matrix.extend_right(bracket_right);

				int32_t add_height = y_origin - new_y_origin;
				if (add_height < 0) { equation_part.extend_up(-add_height, false); y_origin -= add_height; }
				else symbol_matrix.extend_up(add_height, false);
				add_height = symbol_matrix.height() - equation_part.height();
				if (add_height > 0) equation_part.extend_down(add_height, false);
				else symbol_matrix.extend_down(-add_height, false);
				equation_part.extend_right(symbol_matrix);
			}
			render_index.pop_back();
		}
		equation_part.push_back(DynamicBitset(equation_part.height(), false));
	}
	render_index.back()++;
	if (render_index == cursor_index) cursor_data_new = { equation_part.width() - 1, 0, font_height };
	cursor_data_new.y += y_origin;
	y_origin_ref = y_origin;
	if (cursor_data_new.size != 0) cursor_data = cursor_data_new;
	return equation_part;
}

std::vector<Equation::EquationNode*>* Equation::format_equation_part(const std::vector<EquationNode*>* equation, uint32_t& i, bool return_on_closed_bracket) {
	std::vector<Equation::EquationNode*>* new_equation = new std::vector<Equation::EquationNode*>(0);
	if (equation->size() == 0) {
		return new_equation;
	}
	while (i < equation->size()) {
		if (equation->at(i)->children == nullptr) {
			if (std::count(singleBracketOpenKeys.begin(), singleBracketOpenKeys.end(), *equation->at(i)->value) != 0) {
				std::vector<Equation::EquationNode*>* equation_temp = format_equation_part(equation, ++i, true);
				if (equation_temp->size() == 0) {
					new_equation->push_back(new EquationNode{ new uint8_t(74), nullptr });
				}
				else {
					new_equation->push_back(new EquationNode{ new uint8_t(74), new std::vector<Equation::EquationNode*>{ new EquationNode{nullptr, equation_temp }} });
				}
			}
			else if (*equation->at(i)->value == 75 && return_on_closed_bracket) { new_equation->push_back(equation->at(i++)); break; }
			else new_equation->push_back(equation->at(i++));
		}
		else {
			std::vector<Equation::EquationNode*>* sub_equations = new std::vector<Equation::EquationNode*>(0);
			for (int j = 0; j < equation->at(i)->children->size(); j++) {
				uint32_t new_i = 0;
				sub_equations->push_back(new EquationNode{ nullptr, format_equation_part(equation->at(i)->children->at(j)->children, new_i, false)});
 			}
			new_equation->push_back(new EquationNode{ equation->at(i++)->value, sub_equations});
		}
	}
	return new_equation;
}

Equation::EquationNode* Equation::format_equation(const EquationNode* equation) {
	uint32_t i = 0;
	return new EquationNode{ nullptr, format_equation_part(_equation_root_raw->children, i, false) };
}

double Equation::calculate_equation(const std::vector<double> variables, Error& error) {
	CalculateNode* calculation = calculate_equation_part(*_equation_root_raw->children, error);
	return *calculation->value;
}

Equation::CalculateNode* Equation::calculate_equation_part(const std::vector<EquationNode*>& equation, Error& error) {
	if (equation.size() == 0) {
		cursor_index = std::vector<uint32_t>{0};
		error = Error::SYNTAX_ERROR;
		return nullptr;
	}
	std::vector<CalculateNode> calculation(0);
	bool negative = false;
	bool numExpected = true;
	bool insideFunction = false;
	std::string num;
	for (size_t i = 0; i < equation.size(); i++) {
		if (equation[i]->children != nullptr) {
			std::vector<CalculateNode*> subEquations;
			Error err;
			for (EquationNode* node : *equation[i]->children) {
				subEquations.push_back(calculate_equation_part(*node->children, err));
				switch (err) {
				case Error::MATH_ERROR:
					;
				case Error::PUFFER_ERROR:
					;
				case Error::SYNTAX_ERROR:
					;
				case Error::ARGUMENT_ERROR:
					;
				case Error::STORAGE_ERROR:
					;
				case Error::TIME_ERROR:
					;
				case Error::FINE:
					;
				}
			}
			switch (*equation[i]->value) {
			case 110: calculation.push_back(CalculateNode(new double(*subEquations[0]->value / *subEquations[1]->value), nullptr));
			}
		}
		else {
			uint8_t value = *equation[i]->value;
			if (value < 10) {
				num.push_back(value + 48);
			}
			else if (value == Chars::KEY_MAP.at(".")) {
				num.push_back('.');
			}
			else if (value == Chars::KEY_MAP.at("*10^n")) {
				num.push_back('e');
			}
			else {
				if (num != "") {
					calculation.push_back(CalculateNode(new double(std::stod(num)), nullptr));
					num = "";
				}

				if (std::count(allowedCalculateOperations.begin(), allowedCalculateOperations.end(), value) || (value > 189 && value < 236)) {
					calculation.push_back(CalculateNode(nullptr, new uint8_t(value)));
				}
				else {
					switch (value) {
					case 10:;
					}
				}
			}
		}
	}
	if (num != "") {
		calculation.push_back(CalculateNode(new double(std::stod(num)), nullptr));
		num = "";
	}

	// TODO: calculate result from calculation



	return nullptr;
}


void Equation::add_value(uint8_t keypress) {
	EquationNode* modify;
	modify = _equation_root_raw;
	for (size_t i = 0; i < cursor_index.size() - 1; i++) {
		modify = modify->children->at(cursor_index[i]);
	}

	uint8_t valueCnt;
	bool addFirstValue = true;
	switch (keypress) {
	case 110: valueCnt = 2; break;
	case 131: valueCnt = 3; break;
	default: valueCnt = 0; break;
	}

	if (valueCnt != 0) {
		EquationNode* container = new EquationNode();
		container->value = new uint8_t(keypress);
		container->children = new std::vector<EquationNode*>(valueCnt);
		for (uint8_t i = 0; i < valueCnt; i++) {
			container->children->at(i) = new EquationNode();
			container->children->at(i)->children = new std::vector<EquationNode*>(0);
		}

		uint32_t end = cursor_index.back();
		while (cursor_index.back() != 0) {
			uint8_t val = *modify->children->at(cursor_index.back() - 1)->value;
			if (!(val < 10 || val == 82 || val == 127 || modify->children->at(cursor_index.back() - 1)->children != nullptr)) break;
			cursor_index.back()--;
		}
		if (end != cursor_index.back()) {
			auto ptrBegin = modify->children->begin() + cursor_index.back();
			auto ptrEnd = modify->children->begin() + end;
			*container->children->at(0)->children = { ptrBegin, ptrEnd };
			modify->children->erase(ptrBegin, ptrEnd);
			auto ptr = modify->children->begin() + cursor_index.back();
			modify->children->insert(ptr, container);
			if (valueCnt > 1) {
				cursor_index.push_back(1);
				cursor_index.push_back(0);
			}
			else {
				cursor_index.back()++;
			}
		}
		else {
			auto ptr = modify->children->begin() + cursor_index.back();
			modify->children->insert(ptr, container);
			cursor_index.push_back(0);
			cursor_index.push_back(0);
		}
	}
	else {
		EquationNode* container = new EquationNode();
		container->value = new uint8_t(keypress);
		std::vector<EquationNode*>::iterator ptr = modify->children->begin();
		advance(ptr, cursor_index.back());
		modify->children->insert(ptr, container);
		cursor_index.back() += 1;
	}
	equation_changed = true;
}

void Equation::move_cursor_left() {
	EquationNode* modify;
	EquationNode* modify_parent;
	modify_parent = modify = _equation_root_raw;
	uint32_t i = 0;
	for (; i + 1 < cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursor_index[i]);
	}
	if (cursor_index.back() != 0) {
		if (modify->children->at(cursor_index.back() - 1)->children != nullptr) {
			cursor_index.back() -= 1;
			std::vector<EquationNode*>* modify_child = modify->children->at(cursor_index.back())->children;
			cursor_index.push_back(modify_child->size() - 1);
			cursor_index.push_back(modify_child->at(cursor_index.back())->children->size());
		}
		else {
			cursor_index.back() -= 1;
		}
	}
	else if (cursor_index.size() == 1) {
		cursor_index.back() = modify->children->size();
	}
	else if (cursor_index[i - 1] != 0) {
		cursor_index[i - 1] -= 1;
		cursor_index[i] = modify_parent->children->at(cursor_index[i - 1])->children->size();
	}
	else {
		cursor_index.pop_back();
		cursor_index.pop_back();
	}
	equation_changed = true;
}

void Equation::move_cursor_right() {
	EquationNode* modify;
	EquationNode* modify_parent;
	modify_parent = modify = _equation_root_raw;
	size_t i = 0;
	for (; i+1 < cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursor_index[i]);
	}
	if (modify->children->size() > cursor_index.back()) {
		if (modify->children->at(cursor_index.back())->children != nullptr) {
			cursor_index.push_back(0);
			cursor_index.push_back(0);
		}
		else {
			cursor_index.back() += 1;
		}
	}
	else if (cursor_index.size() == 1) {
		cursor_index.back() = 0;
	}
	else if (modify_parent->children->size() > cursor_index[i-1] + 1) {
		cursor_index[i-1] += 1;
		cursor_index[i] = 0;
	}
	else {
		cursor_index.pop_back();
		cursor_index.pop_back();
		cursor_index.back() += 1;
	}
	equation_changed = true;
}

void Equation::move_cursor_up() {
	EquationNode* modify = _equation_root_raw;
	for (int i = 0; i + 1 < cursor_index.size() - 1; i++) modify = modify->children->at(cursor_index[i]);

	if (*modify->value == 110 && cursor_index[cursor_index.size() - 2] == 1) {
		cursor_index[cursor_index.size() - 2] = 0;
		cursor_index.back() = modify->children->at(0)->children->size();
		equation_changed = true;
	}
}

void Equation::move_cursor_down() {
	EquationNode* modify = _equation_root_raw;
	for (int i = 0; i + 1 < cursor_index.size() - 1; i++) {
		modify = modify->children->at(cursor_index[i]);
	}
	if (*modify->value == 110 && cursor_index[cursor_index.size() - 2] == 0) {
		cursor_index[cursor_index.size() - 2] = 1;
		cursor_index.back() = 0;
		equation_changed = true;
	}
}

void Equation::del() {
	EquationNode* modify;
	EquationNode* modify_parent;
	modify_parent = modify = _equation_root_raw;
	size_t i = 0;
	for (; i + 1 < cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursor_index[i]);
	}
	if (cursor_index.back() != 0 && modify->children->at(cursor_index.back() - 1)->children == nullptr) {
		modify->children->erase(modify->children->begin() + cursor_index.back() - 1);
		cursor_index.back() -= 1;
	}
	else {
		if (cursor_index.back() == 0 && modify_parent->children->size() > cursor_index[i - 1] + 1) {
			if (cursor_index.size() == 1) return;
			cursor_index.pop_back();
			cursor_index.pop_back();
			EquationNode* modify;
			EquationNode* modify_parent;
			modify_parent = modify = _equation_root_raw;
			size_t i = 0;
			for (; i + 1 < cursor_index.size(); i++) {
				modify_parent = modify;
				modify = modify->children->at(cursor_index[i]);
			}
			//std::vector<EquationNode*> insert_equation;
			//for (uint32_t i = 0; i < modify->children->size(); i++) {
			//	insert_equation.insert(insert_equation.end(), modify->children->at(i)->children->begin(), modify->children->at(i)->children->end());
			//}
			modify_parent->children->erase(modify_parent->children->begin() + cursor_index.back());
			//modify_parent->children->insert(modify_parent->children->begin() + cursor_index.back(), insert_equation.begin(), insert_equation.end());
		}
		else {
			move_cursor_left();
		}
	}
	equation_changed = true;
}

void Equation::ac() {
	delete _equation_root_raw;
	_equation_root_raw = new EquationNode();
	_equation_root_raw->children = new std::vector<EquationNode*>(0);
	cursor_index = std::vector<uint32_t>{0};
	equation_changed = true;
}