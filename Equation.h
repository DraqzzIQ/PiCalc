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
	void addValue(uint8_t value);
	void calculate();
	void del();
	void moveCursorLeft();
	void moveCursorRight();
private:
	std::vector<int> cursor_position = std::vector<int>(1, 0);
	enum class Operation {
		FRACTION,
		MIXED_FRACTION,
		ROOT,
		LOG,
		POWER
	};

	struct Node {
		uint8_t* value;
		Operation* operation;
		std::vector<Node*>* children;
	};
	Node root;
	render_plane renderedEquation;
	bool equationChanged;

	render_plane renderEquationPart(std::vector<Node*> equation, std::map<uint8_t, render_plane> table);
	render_plane renderFraction(render_plane top, render_plane bottom);
	render_plane resize_center_x(render_plane renderPlaneInput, int length);
	void add_resized_symbol(render_plane &renderPlane, render_plane symbol, int y_position);
};
