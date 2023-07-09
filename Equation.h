#pragma once
#include <vector>
#include "Window.h"
#include <string>


class Equation
{
public:
	Equation();
	~Equation();
	render_plane renderEquation();
	void moveCursor(char direction);
	void addValue(wchar_t Value);
	//void del();
private:
	std::vector<int> cursor_position = std::vector<int>(1, 0);
	struct Node {
		wchar_t* value;
		wchar_t* operation;
		std::vector<Node*>* children;
	};
	Node root;

	//std::vector<int> moveCursorLeft(std::vector<int> cursorPosition);
	std::vector<int> moveCursorRight(std::vector<int> cursorPosition);
};
