#include "Equation.h"

Equation::Equation() {
	root = new RenderNode();
	root->children = new std::vector<RenderNode*>(0);
	cursor_index = std::vector<uint16_t>{0};

	last_blink_time = Utils::us_since_boot();
	equation_changed = true;
	show_cursor = true;
}

Equation::~Equation() {
	delete root;
}

bitset_2d Equation::render_equation() {
	if (equation_changed) {
		// the equation is empty
		if (root->children->size() == 0) {
			rendered_equation = bitset_2d();
			rendered_equation_cursor = bitset_2d(2, 9, true);
		}
		else {
			cursorData cursor_data{ 2, 2, 2 };
			rendered_equation = render_equation_part(*root->children, Graphics::SYMBOLS_9_HIGH, std::vector<uint16_t>(), cursor_data);
			rendered_equation_cursor = rendered_equation;
			rendered_equation_cursor.set(cursor_data.x, cursor_data.y, bitset_2d(2, cursor_data.size, true), true);
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

bitset_2d Equation::render_equation_part(const std::vector<RenderNode*>& equation, const std::map<uint8_t, bitset_2d>& table, std::vector<uint16_t> render_index, cursorData& cursor_data) {
	uint8_t font_height = table.at(0).height();
	// top left corner of the first value
	uint32_t y_origin = 0;
	bitset_2d equation_part(1, font_height, false);
	cursorData cursor_data_new = { 0, 0, 0 };
	render_index.push_back(0);

	if (equation.size() == 0) {
		if (render_index == cursor_index) cursor_data = { 0, 0, font_height };
		return table.at(Chars::KEY_MAP.at("empty"));
	}
	for (size_t i = 0; i < equation.size(); i++) {
		RenderNode* current_symbol = equation.at(i);
		bitset_2d symbol_matrix = bitset_2d();
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
			std::vector<bitset_2d> sub_equations;
			int8_t subequation_cursor_index = -1;
			render_index.push_back(0);
			for (uint32_t j = 0; j < current_symbol->children->size(); j++) {
				render_index.back() = j;
				cursorData cursor_data_subequation = { 0, 0, 0 };
				sub_equations.push_back(render_equation_part(*current_symbol->children->at(j)->children, Graphics::SYMBOLS_6_HIGH, render_index, cursor_data_subequation));
				if (cursor_data_subequation.size != 0) { subequation_cursor_index = j; cursor_data_new = cursor_data_subequation;  }
			}
			render_index.pop_back();

			if (*current_symbol->value == Chars::KEY_MAP.at("fraction")) {
 				int32_t diff = sub_equations[1].width() - sub_equations[0].width();
				if (diff > 0) {
					sub_equations[0].extend_right(diff / 2, false);
					sub_equations[0].extend_left((diff + 1) / 2, false);
					if (subequation_cursor_index == 0) cursor_data_new.x += (diff + 1) / 2;
				}
				else if (diff < 0) {
					sub_equations[1].extend_right(-diff / 2, false);
					sub_equations[1].extend_left((-diff + 1) / 2, false);
					if (subequation_cursor_index == 1) cursor_data_new.x += (-diff + 1) / 2;
				}

				for (int i = 0; i < sub_equations[0].width(); i++) {
					dynamic_bitset column = sub_equations[0][i];
					column.push_back(false);
					column.push_back(true);
					column.push_back(false);
					column.insert(column.size(), sub_equations[1][i]);
					symbol_matrix.push_back(column);
				}


				uint8_t fraction_line_height = (font_height == 9) ? 3 : 2;

				if (subequation_cursor_index != -1) {
					cursor_data_new.x += equation_part.width();
					if (subequation_cursor_index == 0)
						cursor_data_new.y += fraction_line_height - sub_equations[0].height();
					else if (subequation_cursor_index == 1)
						cursor_data_new.y += fraction_line_height + 3;
				}

				int32_t add_height = y_origin + fraction_line_height - sub_equations[0].height();
				if (add_height < 0) { equation_part.extend_up(-add_height, false); y_origin -= add_height; }
				else symbol_matrix.extend_up(add_height, false);
				add_height = symbol_matrix.height() - equation_part.height();
				if (add_height > 0) equation_part.extend_down(add_height, false);
				else symbol_matrix.extend_down(-add_height, false);
				equation_part.extend_right(symbol_matrix);
			}
		}
		equation_part.push_back(dynamic_bitset(equation_part.height(), false));
	}
	render_index.back()++;
	if (render_index == cursor_index) cursor_data_new = { equation_part.width() - 1, 0, font_height };
	cursor_data_new.y += y_origin;
	if (cursor_data_new.size != 0) cursor_data = cursor_data_new;
	return equation_part;
}

//bitset_2d Equation::render_fraction(const bitset_2d& top, const bitset_2d& bottom) {
//	int length = std::max(top.width(), bottom.width()) + 1;
//	bitset_2d top_resized = resize_center_x(top, length);
//	bitset_2d bottom_resized = resize_center_x(bottom, length);
//	bitset_2d combined = bitset_2d();
//
//	for (int i = 0; i < length; i++) {
//		dynamic_bitset column = top_resized[i];
//		column.push_back(false);
//		column.push_back(true);
//		column.push_back(false);
//		column.insert(column.size(), bottom_resized[i]);
//		combined.push_back(column);
//	}
//
//	return combined;
//}
//
//bitset_2d Equation::resize_center_x(const bitset_2d& bitset_2d_input, uint16_t length) {
//	dynamic_bitset empty = dynamic_bitset(bitset_2d_input.at(0).size(), false);
//	bitset_2d resized_bitset_2d = bitset_2d(std::floor((length - bitset_2d_input.width()) / 2), empty);
//	resized_bitset_2d.extend_right(bitset_2d_input);
//	int s = resized_bitset_2d.width();
//	for (int i = 0; i < length - s; i++) {
//		resized_bitset_2d.push_back(empty);
//	}
//	return resized_bitset_2d;
//}

double Equation::calculate_equation(Error& error) {
	CalculateNode* calculation = calculate_equation_part(*root->children, error);
	return *calculation->value;
}

Equation::CalculateNode* Equation::calculate_equation_part(const std::vector<RenderNode*>& equation, Error& error) {
	if (equation.size() == 0) {
		cursor_index = std::vector<uint16_t>{0};
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
			for (RenderNode* node : *equation[i]->children) {
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
			case 131:;
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
	RenderNode* modify;
	modify = root;
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
		RenderNode* container = new RenderNode();
		container->value = new uint8_t(keypress);
		container->children = new std::vector<RenderNode*>(valueCnt);
		for (uint8_t i = 0; i < valueCnt; i++) {
			container->children->at(i) = new RenderNode();
			container->children->at(i)->children = new std::vector<RenderNode*>(0);
		}

		uint8_t end = cursor_index.back();
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
		RenderNode* container = new RenderNode();
		container->value = new uint8_t(keypress);
		std::vector<RenderNode*>::iterator ptr = modify->children->begin();
		advance(ptr, cursor_index.back());
		modify->children->insert(ptr, container);
		cursor_index.back() += 1;
	}
	equation_changed = true;
}

void Equation::move_cursor_left() {
	RenderNode* modify;
	RenderNode* modify_parent;
	modify_parent = modify = root;
	size_t i = 0;
	for (; i + 1 < cursor_index.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursor_index[i]);
	}
	if (cursor_index.back() != 0) {
		if (modify->children->at(cursor_index.back() - 1)->children != nullptr) {
			cursor_index.back() -= 1;
			std::vector<RenderNode*>* modify_child = modify->children->at(cursor_index.back())->children;
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
	RenderNode* modify;
	RenderNode* modify_parent;
	modify_parent = modify = root;
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

void Equation::del() {
	RenderNode* modify = root;
	for (size_t i = 0; i + 1 < cursor_index.size(); i++) {
		modify = modify->children->at(cursor_index[i]);
	}
	if (cursor_index.back() != 0 && modify->children->at(cursor_index.back() - 1)->children == nullptr) {
		modify->children->erase(modify->children->begin() + cursor_index.back() - 1);
		cursor_index.back() -= 1;
	}
	else {
		move_cursor_left();
		del();
	}
	equation_changed = true;
}