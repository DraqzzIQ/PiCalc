#pragma once
#include "Window.h"
#include "Graphics.h"
#include "KeyPress.h"
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>


class Equation
{
public:
	Equation();
	~Equation();
	render_plane render_equation();
	void add_value(uint8_t keypress);
	double calculate_equation();
	void del();
	void move_cursor_left();
	void move_cursor_right();
private:
	enum class Error {
		MATH_ERROR,
		PUFFER_ERROR,
		SYNTAX_ERROR,
		ARGUMENT_ERROR,
		STORAGE_ERROR,
		TIME_ERROR,
		FINE,
	};

	struct RenderNode {
		uint8_t* value;
		std::vector<RenderNode*>* children;

		~RenderNode() {
			delete value;
			delete operation;
			for (RenderNode* child : *children) {
				delete child;
			}
			delete children;
		}
	};
	RenderNode* root;

	std::vector<uint8_t> allowedCalculateOperations {
		69, 70, 71, 72, 74, 75, 85, 98, 114, 115, 118, 119, 120, 130, 138, 139, 140, 152, 153, 154, 159, 162, 163, 164
	};

	struct CalculateNode {
		double* value;
		uint8_t* operation;
		~CalculateNode() {
			delete value;
			delete operation;
		}
	};

	std::vector<double> letterVariables = std::vector<double>(9, 0.0);


	render_plane rendered_equation;
	bool equation_changed;
	std::vector<int> cursor_position = std::vector<int>(1, 0);
	  
	CalculateNode* calculate_equation_part(std::vector<RenderNode*> equation, Error& error);
	render_plane render_equation_part(std::vector<RenderNode*> equation, std::map<uint8_t, render_plane> table);
	render_plane render_fraction(render_plane top, render_plane bottom);
	render_plane resize_center_x(render_plane render_plane_input, int length);
	void add_resized_symbol(render_plane &resized_render_plane, render_plane symbol, int y_position);
};
