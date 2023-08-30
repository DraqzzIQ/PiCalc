#include "Equation.h"

Equation::Equation() {
	root = new RenderNode();
	root->children = new std::vector<RenderNode*>(0);
	equation_changed = true;
	rendered_equation = render_plane();
}

Equation::~Equation() 
{
	delete root;
}

render_plane Equation::render_equation() {
	if (equation_changed) {
		rendered_equation = render_equation_part(*root->children, Graphics::SYMBOLS_9_HIGH);
		equation_changed = false;
	}
	return rendered_equation;
}

render_plane Equation::render_equation_part(std::vector<RenderNode*> equation, std::map<uint8_t, render_plane> table) {
	int font_height = table.at(' ').at(0).size();
	int y_origin = 0;
	render_plane equation_part = render_plane(1, std::vector<bool>(font_height, false));

	if (equation.size() == 0) {
		return table.at(Chars::KEY_MAP.at("empty"));
	}
	for (size_t i = 0; i < equation.size(); i++) {
		RenderNode* current_symbol = equation.at(i);

		if (current_symbol->operation == nullptr) {
			render_plane symbol_matrix;
			if (table.count(*current_symbol->value) != 0) symbol_matrix = table.at(*current_symbol->value);
			else symbol_matrix = table.at(Chars::KEY_MAP.at("?"));
			add_resized_symbol(equation_part, symbol_matrix, y_origin);
		}

		else {
			std::vector<render_plane> sub_equations;
			for (RenderNode* node : *current_symbol->children) {
				sub_equations.push_back(render_equation_part(*node->children, Graphics::SYMBOLS_6_HIGH));
			}

			if (*current_symbol->operation == SymbolOperation::FRACTION) {
				int fraction_height = (font_height == 9) ? 3 : 2;
				int add_height = y_origin + fraction_height - sub_equations[0][0].size();
				if (add_height < 0) {
					std::vector<bool> empty = std::vector<bool>(-add_height, false);
					for (int i = 0; i < equation_part.size(); i++) {
						equation_part[i].insert(equation_part[i].begin(), empty.begin(), empty.end());
					}
					y_origin -= add_height;
				}

				add_height = sub_equations[0][0].size() + sub_equations[1][0].size() + 3 - equation_part[0].size();
				if (add_height > 0) {
					std::vector<bool> empty = std::vector<bool>(add_height, false);
					for (int i = 0; i < equation_part.size(); i++) {
						equation_part[i].insert(equation_part[i].end(), empty.begin(), empty.end());
					}
				}

				render_plane rendered_fraction = render_fraction(sub_equations[0], sub_equations[1]);
				add_resized_symbol(equation_part, rendered_fraction, y_origin + fraction_height - sub_equations[0][0].size());
			}
		}
		if (i + 1 != equation.size())
			equation_part.push_back(std::vector<bool>(equation_part[0].size(), false));
	}
	equation_part.erase(equation_part.begin());
	return equation_part;
}

render_plane Equation::render_fraction(render_plane top, render_plane bottom) {
	int length = std::max(top.size(), bottom.size()) + 2;
	render_plane top_resized = resize_center_x(top, length);
	render_plane bottom_resized = resize_center_x(bottom, length);
	render_plane combined = render_plane();

	for (int i = 0; i < length; i++) {
		std::vector<bool> column = top_resized[i];
		column.push_back(false);
		column.push_back(true);
		column.push_back(false);
		column.insert(column.end(), bottom_resized[i].begin(), bottom_resized[i].end());
		combined.push_back(column);
	}

	return combined;
}

render_plane Equation::resize_center_x(render_plane render_plane_input, int length) {
	std::vector<bool> empty = std::vector<bool>(render_plane_input[0].size(), false);
	render_plane resized_render_plane = render_plane(std::floor((length - render_plane_input.size()) / 2), empty);
	resized_render_plane.insert(resized_render_plane.end(), render_plane_input.begin(), render_plane_input.end());
	int s = resized_render_plane.size();
	for (int i = 0; i < length - s; i++) {
		resized_render_plane.push_back(empty);
	}
	return resized_render_plane;
}

void Equation::add_resized_symbol(render_plane& resized_render_plane, render_plane symbol, int y_position) {
	std::vector<bool> empty_top = std::vector<bool>(y_position, false);
	std::vector<bool> empty_bottom = std::vector<bool>(resized_render_plane[0].size() - y_position - symbol[0].size(), false);
	for (int i = 0; i < symbol.size(); i++) {
		std::vector<bool> column = empty_top;
		column.insert(column.end(), symbol[i].begin(), symbol[i].end());
		column.insert(column.end(), empty_bottom.begin(), empty_bottom.end());
		resized_render_plane.push_back(column);
	}
}

void Equation::calculate_equation(int8_t& exponent, int64_t& value) {
	Error error;
	CalculateNode* calculation = calculate_equation_part(*root->children, error);
	switch (error) {
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

Equation::CalculateNode* Equation::calculate_equation_part(std::vector<RenderNode*> equation, Error& error) {
	if (equation.size() == 0) {
		cursor_position = std::vector<int>(0, 0);
		error = Error::SYNTAX_ERROR;
		return nullptr;
	}
	std::vector<CalculateNode> calculation(0);
	bool negative = false;
	bool numExpected = true;
	for (size_t i = 0; i < equation.size(); i++) {
		if (equation[i]->operation != nullptr) {
			int8_t exp;
			int64_t val;
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
			switch (*equation[i]->operation) {
				case SymbolOperation::FRACTION:
					;
				
			}
			//calculate_equation_part(*equation[i]->children, val, exp);
			//if () {

			//}
		}
		//if (*equation[i]->value < 10) {
		//	
		//}
		//if (calculation.size() == 0 || ) {

		//}
	}
	return nullptr;
}


void Equation::add_value(uint8_t keypress) {
	RenderNode* modify;
	modify = root;
	for (size_t i = 0; i < cursor_position.size() - 1; i++) {
		modify = modify->children->at(cursor_position[i]);
	}

	// todo: unite all multi-Input symbols into one function
	// if value before multi-Input symbol: transfer Value to 1st child of multi-input symbol
	if (keypress == Chars::KEY_MAP.at("fraction")) {
		RenderNode* container = new RenderNode();
		container->operation = new SymbolOperation(SymbolOperation::FRACTION);
		container->children = new std::vector<RenderNode*>(2);
		container->children->at(0) = new RenderNode();
		container->children->at(1) = new RenderNode();
		container->children->at(0)->children = new std::vector<RenderNode*>(0);
		container->children->at(1)->children = new std::vector<RenderNode*>(0);
		std::vector<RenderNode*>::iterator ptr = modify->children->begin();
		advance(ptr, cursor_position.back());
		modify->children->insert(ptr, container);
		cursor_position.push_back(0);
		cursor_position.push_back(0);
	}
	else if (keypress == Chars::KEY_MAP.at("root2"))
	{
		;
	}
	else {
		RenderNode* container = new RenderNode();
		container->value = new uint8_t(keypress);
		std::vector<RenderNode*>::iterator ptr = modify->children->begin();
		advance(ptr, cursor_position.back());
		modify->children->insert(ptr, container);
		cursor_position.back() += 1;
	}
	equation_changed = true;
}

void Equation::move_cursor_left() {
	RenderNode* modify;
	RenderNode* modify_parent;
	modify_parent = modify = root;
	size_t i = 0;
	for (; i + 1 < cursor_position.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursor_position[i]);
	}
	if (cursor_position.back() != 0) {
		if (modify->children->at(cursor_position.back() - 1)->operation != nullptr) {
			cursor_position.back() -= 1;
			std::vector<RenderNode*>* modify_child = modify->children->at(cursor_position.back())->children;
			cursor_position.push_back(modify_child->size() - 1);
			cursor_position.push_back(modify_child->at(cursor_position.back())->children->size());
		}
		else {
			cursor_position.back() -= 1;
		}
	}
	else if (cursor_position.size() == 1) {
		cursor_position.back() = modify->children->size();
	}
	else if (cursor_position[i - 1] != 0) {
		cursor_position[i - 1] -= 1;
		cursor_position[i] = modify_parent->children->at(cursor_position[i - 1])->children->size();
	}
	else {
		cursor_position.pop_back();
		cursor_position.pop_back();
	}
}

void Equation::move_cursor_right() {
	RenderNode* modify;
	RenderNode* modify_parent;
	modify_parent = modify = root;
	size_t i = 0;
	for (; i+1 < cursor_position.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursor_position[i]);
	}
	if (modify->children->size() > cursor_position.back()) {
		if (modify->children->at(cursor_position.back())->operation != nullptr) {
			cursor_position.push_back(0);
			cursor_position.push_back(0);
		}
		else {
			cursor_position.back() += 1;
		}
	}
	else if (cursor_position.size() == 1) {
		cursor_position.back() = 0;
	}
	else if (modify_parent->children->size() > cursor_position[i-1] + 1) {
		cursor_position[i-1] += 1;
		cursor_position[i] = 0;
	}
	else {
		cursor_position.pop_back();
		cursor_position.pop_back();
		cursor_position.back() += 1;
	}
}

void Equation::del() {
	RenderNode* modify = root;
	for (size_t i = 0; i + 1 < cursor_position.size(); i++) {
		modify = modify->children->at(cursor_position[i]);
	}
	if (cursor_position.back() != 0 && modify->children->at(cursor_position.back() - 1)->operation == nullptr) {
		modify->children->erase(modify->children->begin() + cursor_position.back() - 1);
		cursor_position.back() -= 1;
	}
	else {
		move_cursor_left();
		del();
	}
	equation_changed = true;
}