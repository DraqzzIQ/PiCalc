#pragma once
#include "Window.h"
#include "Graphics.h"
#include <vector>
#include <string>
#include <map>
#include <cmath>


class Equation
{
public:
	Equation();
	~Equation();
	render_plane renderEquation();
	void add_value(uint8_t value);
	void calculate();
	void del();
	void move_cursor_left();
	void move_cursor_right();
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
	Node* root;
	render_plane rendered_equation;
	bool equation_changed;

	render_plane render_equation_part(std::vector<Node*> equation, std::map<uint8_t, render_plane> table);
	render_plane render_fraction(render_plane top, render_plane bottom);
	render_plane resize_center_x(render_plane render_plane_input, int length);
	void add_resized_symbol(render_plane &plane_to_render, render_plane symbol, int y_position);
};
