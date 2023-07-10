#include "Equation.h"

Equation::Equation() {
	root = Node();
	root.children = new std::vector<Node*>(0);
}

Equation::~Equation() {
	
}

render_plane Equation::renderEquation() {
	return renderEquationPart(*root.children, Graphics::SYMBOLS_9_HIGH);
}

render_plane Equation::renderEquationPart(std::vector<Node*> equation, std::map<wchar_t, render_plane> table) {
	size_t height = table.at(' ').at(0).size();
	size_t fractionHeight = (height == 9) ? 4 : 3;
	size_t yStart = 0;
	render_plane renderPlane;
	renderPlane = std::vector<std::vector<bool>>(2, std::vector<bool>(height, false));
	std::vector<bool> empty = std::vector<bool>(height, false);
	for (size_t i = 0; i < equation.size(); i++) {
		Node* container = equation.at(i);
		if (container->operation == nullptr) {
			if (Graphics::SYMBOLS_9_HIGH.count(*container->value) != 0) {
				renderPlane.insert(renderPlane.end(), table.at(*container->value).begin(), table.at(*container->value).end());
			}
		}
		else {
			if (*container->operation == FRACTION) {
				render_plane top = renderEquationPart(*container->children->at(0)->children, Graphics::SYMBOLS_6_HIGH);
				render_plane bottom = renderEquationPart(*container->children->at(0)->children, Graphics::SYMBOLS_6_HIGH);

				renderPlane.insert(renderPlane.end(), table.at('-').begin(), table.at('-').end());
			}
		}

		if (i + 1 != equation.size()) {
			renderPlane.push_back(empty);
		}
	}
	return renderPlane;
}

void Equation::addValue(wchar_t value) {
	Node* modify;
	modify = &root;
	for (size_t i = 0; i < cursor_position.size() - 1; i++) {
		modify = modify->children->at(cursor_position[i]);
	}

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