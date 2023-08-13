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
	void calculateEquation(int8_t& exponent, int64_t& value);
	void del();
	void moveCursorLeft();
	void moveCursorRight();
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
	RenderNode root;

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

	render_plane renderedEquation;
	bool equationChanged;
	std::vector<int> cursor_position = std::vector<int>(1, 0);
	  
	CalculateNode* calculateEquationPart(std::vector<RenderNode*> equation, Error& error);
	render_plane renderEquationPart(std::vector<RenderNode*> equation, std::map<uint8_t, render_plane> table);
	render_plane renderFraction(render_plane top, render_plane bottom);
	render_plane resize_center_x(render_plane renderPlaneInput, int length);
	void add_resized_symbol(render_plane &renderPlane, render_plane symbol, int y_position);
};
