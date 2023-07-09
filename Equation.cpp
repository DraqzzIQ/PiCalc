#include "Equation.h"
#include "SpecialChars.h"
#include <iterator>

Equation::Equation() {
	root = Node();
	root.children = new std::vector<Node*>(0);
}

Equation::~Equation() {
	
}

render_plane Equation::renderEquation() {

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