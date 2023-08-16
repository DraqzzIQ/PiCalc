#pragma once
#include "Window.h"
#include "Graphics.h"
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "KeyPress.h"


class Equation
{
public:
	Equation();
	~Equation();
	render_plane render_equation();
	void add_value(uint8_t keypress);
	void calculate_equation(int8_t& exponent, int64_t& value);
	void del();
	void move_cursor_left();
	void move_cursor_right();
private:
	enum class SymbolOperation {
		FRACTION,
		MIXED_FRACTION,
		ROOT,
		LOG,
		POWER
	};

	enum class Error {
		MATH_ERROR,
		PUFFER_ERROR,
		SYNTAX_ERROR,
		ARGUMENT_ERROR,
		STORAGE_ERROR,
		TIME_ERROR,
		NO_ERROR
	};

	struct RenderNode {
		uint8_t* value;
		SymbolOperation* operation;
		std::vector<RenderNode*>* children;
	};
	RenderNode* root;

	enum class CalculateOperation {
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		NEGATIVE_SIGN,
		POSITIVE_SIGN,
		BRACKET_OPEN,
		BRACKET_CLOSE
	};

	struct CalculateNode {
		int64_t value;
		int8_t exponent;
		CalculateOperation operation;
	};

	render_plane rendered_equation;
	bool equation_changed;
	std::vector<int> cursor_position = std::vector<int>(1, 0);
	  
	CalculateNode* calculate_equation_part(std::vector<RenderNode*> equation, Error& error);
	render_plane render_equation_part(std::vector<RenderNode*> equation, std::map<uint8_t, render_plane> table);
	render_plane render_fraction(render_plane top, render_plane bottom);
	render_plane resize_center_x(render_plane render_plane_input, int length);
	void add_resized_symbol(render_plane &resized_render_plane, render_plane symbol, int y_position);
};
