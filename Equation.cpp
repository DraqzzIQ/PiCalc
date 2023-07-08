#include "Equation.h"
#include "SpecialChars.h"
#include <iterator>

Equation::Equation() {
	root = Node();
	root.children = std::vector<Node*>(0);
}

Equation::~Equation() {
	
}

void Equation::addValue(wchar_t value) {
	Node* modify;
	modify = &root;
	for (size_t i = 0; i < cursor_position.size() - 1; i++) {
		modify = modify->children.at(i);
	}

	if (value == FRACTION) {
		Node* container = new Node();
		container->operation = FRACTION;
		container->children = std::vector<Node*>(2);
		container->children[0] = new Node();
		container->children[1] = new Node();
		std::vector<Node*>::iterator ptr = modify->children.begin();
		advance(ptr, cursor_position.back());
		modify->children.insert(ptr, container);
		cursor_position.push_back(0);
	}
	else if (value == SQUARE_ROOT)
	{
		;
	}
	else {
		Node* container = new Node();
		container->value = value;
		std::vector<Node*>::iterator ptr = modify->children.begin();
		advance(ptr, cursor_position.back());
		modify->children.insert(ptr, container);
		cursor_position.back() += 1;
	}
}

void moveCursor(char direction) {

}