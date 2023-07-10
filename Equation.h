#pragma once
#include "Window.h"
#include "Graphics.h"
#include <vector>
#include <string>
#include <map>


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
	render_plane renderEquationPart(std::vector<Node*> equation, std::map<wchar_t, render_plane> table);
};
