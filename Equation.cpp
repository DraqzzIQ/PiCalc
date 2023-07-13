#include "Equation.h"
#include <iostream>

Equation::Equation() {
	root = Node();
	root.children = new std::vector<Node*>(0);
	equationChanged = true;
}

Equation::~Equation() {
	
}

render_plane Equation::renderEquation() {
	if (equationChanged) {
		renderedEquation = renderEquationPart(*root.children, Graphics::SYMBOLS_9_HIGH);
		equationChanged = false;
	}
	return renderedEquation;
}

render_plane Equation::renderEquationPart(std::vector<Node*> equation, std::map<wchar_t, render_plane> table) {
	int font_height = table.at(' ').at(0).size();
	int y_origin = 0;
	render_plane renderPlane = render_plane(1, std::vector<bool>(font_height, false));;

	if (equation.size() == 0) {
		return table.at(EMPTY);
	}
	for (size_t iSymbol = 0; iSymbol < equation.size(); iSymbol++) {
		Node* currentSymbol = equation.at(iSymbol);

		if (currentSymbol->operation == nullptr) {
			render_plane symbolMatrix;
			if (table.count(*currentSymbol->value) != 0) symbolMatrix = table.at(*currentSymbol->value);
			else symbolMatrix = table.at('?');
			add_resized_symbol(renderPlane, symbolMatrix, y_origin);
		}

		else {
			std::vector<render_plane> subEquations;
			for (Node* node : *currentSymbol->children) {
				subEquations.push_back(renderEquationPart(*node->children, Graphics::SYMBOLS_6_HIGH));
			}

			if (*currentSymbol->operation == FRACTION) {
				int fraction_height = (font_height == 9) ? 3 : 2;
				int add_height = y_origin + fraction_height - subEquations[0][0].size();
				if (add_height < 0) {
					std::vector<bool> empty = std::vector<bool>(-add_height, false);
					for (int i = 0; i < renderPlane.size(); i++) {
						renderPlane[i].insert(renderPlane[i].begin(), empty.begin(), empty.end());
					}
					y_origin -= add_height;
				}

				add_height = subEquations[0][0].size() + subEquations[1][0].size() + 3 - renderPlane[0].size();
				if (add_height > 0) {
					std::vector<bool> empty = std::vector<bool>(add_height, false);
					for (int i = 0; i < renderPlane.size(); i++) {
						renderPlane[i].insert(renderPlane[i].end(), empty.begin(), empty.end());
					}
				}

				render_plane renderedFraction = renderFraction(subEquations[0], subEquations[1]);
				add_resized_symbol(renderPlane, renderedFraction, y_origin + fraction_height - subEquations[0][0].size());
			}
		}
		if (iSymbol + 1 != equation.size()) {
			renderPlane.push_back(std::vector<bool>(renderPlane[0].size(), false));
		}
	}
	renderPlane.erase(renderPlane.begin());
	return renderPlane;
}

render_plane Equation::renderFraction(render_plane top, render_plane bottom) {
	int length = std::max(top.size(), bottom.size()) + 2;
	render_plane topResized = resize_center_x(top, length);
	render_plane bottomResized = resize_center_x(bottom, length);
	render_plane renderPlane = render_plane();

	for (int i = 0; i < length; i++) {
		std::vector<bool> column = topResized[i];
		column.push_back(false);
		column.push_back(true);
		column.push_back(false);
		column.insert(column.end(), bottomResized[i].begin(), bottomResized[i].end());
		renderPlane.push_back(column);
	}

	return renderPlane;
}

render_plane Equation::resize_center_x(render_plane renderPlaneInput, int length) {
	std::vector<bool> empty = std::vector<bool>(renderPlaneInput[0].size(), false);
	render_plane renderPlane = render_plane(std::floor((length - renderPlaneInput.size()) / 2), empty);
	renderPlane.insert(renderPlane.end(), renderPlaneInput.begin(), renderPlaneInput.end());
	int s = renderPlane.size();
	for (int i = 0; i < length - s; i++) {
		renderPlane.push_back(empty);
	}
	return renderPlane;
}

void Equation::add_resized_symbol(render_plane& renderPlane, render_plane symbol, int y_position) {
	std::vector<bool> emptyTop = std::vector<bool>(y_position, false);
	std::vector<bool> emptyBottom = std::vector<bool>(renderPlane[0].size() - y_position - symbol[0].size(), false);
	for (int i = 0; i < symbol.size(); i++) {
		std::vector<bool> column = emptyTop;
		column.insert(column.end(), symbol[i].begin(), symbol[i].end());
		column.insert(column.end(), emptyBottom.begin(), emptyBottom.end());
		renderPlane.push_back(column);
	}
}


void Equation::addValue(wchar_t value) {
	equationChanged = true;
	Node* modify;
	modify = &root;
	for (size_t i = 0; i < cursor_position.size() - 1; i++) {
		modify = modify->children->at(cursor_position[i]);
	}

	// todo: unite all multi-Input symbols into one function
	// if value before multi-Input symbol: transfer Value to 1st child of multi-input symbol
	if (value == FRACTION) {
		Node* container = new Node();
		container->operation = new wchar_t(FRACTION);
		container->children = new std::vector<Node*>(2);
		container->children->at(0) = new Node();
		container->children->at(1) = new Node();
		container->children->at(0)->children = new std::vector<Node*>(0);
		container->children->at(1)->children = new std::vector<Node*>(0);
		std::vector<Node*>::iterator ptr = modify->children->begin();
		advance(ptr, cursor_position.back());
		modify->children->insert(ptr, container);
		cursor_position.push_back(0);
		cursor_position.push_back(0);
	}
	else if (value == SQUARE_ROOT)
	{
		;
	}
	else {
		Node* container = new Node();
		container->value = new wchar_t(value);
		std::vector<Node*>::iterator ptr = modify->children->begin();
		advance(ptr, cursor_position.back());
		modify->children->insert(ptr, container);
		cursor_position.back() += 1;
	}
}

void Equation::moveCursor(char direction) {
	if (direction == 'r') {
		cursor_position = moveCursorRight(cursor_position);
	}
}

//std::vector<int> Equation::moveCursorLeft(std::vector<int> cursorPosition) {
//	return
//}

std::vector<int> Equation::moveCursorRight(std::vector<int> cursorPosition) {
	Node* modify;
	Node* modify_parent;
	modify_parent = modify = &root;
	size_t i = 0;
	for (; i+1 < cursorPosition.size(); i++) {
		modify_parent = modify;
		modify = modify->children->at(cursorPosition[i]);
	}
	if (modify->children->size() > cursorPosition.back()) {
		if (modify->children->at(cursorPosition.back())->operation != nullptr) {
			cursorPosition.push_back(0);
			cursorPosition.push_back(0);
			return cursorPosition;
		}
		else {
			cursorPosition.back() += 1;
			return cursorPosition;
		}
	}
	else if (cursorPosition.size() == 1) {
		cursorPosition.back() = 0;
		return cursorPosition;
	}
	else if (modify_parent->children->size() > cursorPosition[i-1] + 1) {
		cursorPosition[i-1] += 1;
		cursorPosition[i] = 0;
		return cursorPosition;
	}
	else {
		cursorPosition.pop_back();
		cursorPosition.pop_back();
		cursorPosition.back() += 1;
		return cursorPosition;
	}
}