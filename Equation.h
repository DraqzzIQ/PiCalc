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
	void calculate();
	void del();
private:
	std::vector<int> cursor_position = std::vector<int>(1, 0);
	struct Node {
		wchar_t* value;
		wchar_t* operation;
		std::vector<Node*>* children;
	};
	Node root;
	render_plane renderedEquation;
	bool equationChanged;

	void moveCursorLeft();
	void moveCursorRight();
	render_plane renderEquationPart(std::vector<Node*> equation, std::map<wchar_t, render_plane> table);
	render_plane renderFraction(render_plane top, render_plane bottom);
	render_plane resize_center_x(render_plane renderPlaneInput, int length);
	void add_resized_symbol(render_plane &renderPlane, render_plane symbol, int y_position);
};
