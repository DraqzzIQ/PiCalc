#pragma once
#include "Window.h"
#include "Graphics.h"
#include "KeyPress.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>


class Equation
{
public:
	/// <summary>
	/// Construct a new Equation
	/// </summary>
	Equation();
	/// <summary>
	/// delete the Equation and clear allocated Memory
	/// </summary>
	~Equation();
	/// <summary>
	/// enum for all error types
	/// </summary>
	enum class Error { MATH_ERROR, PUFFER_ERROR, SYNTAX_ERROR, ARGUMENT_ERROR, STORAGE_ERROR, TIME_ERROR, FINE };
	/// <summary>
	/// render the Equation
	/// </summary>
	bitset_2d render_equation();
	/// <summary>
	/// add a Value to the equation at the current Cursor position
	/// </summary>
	/// <param name="keypress">Char to add</param>
	void add_value(uint8_t keypress);
	/// <summary>
	/// calculate the equation
	/// </summary>
	/// <returns>result</returns>
	double calculate_equation(const std::vector<double> variables, Error& error);
	/// <summary>
	/// delete the character before the Cursor
	/// </summary>
	void del();
	/// <summary>
	/// delete the character before the Cursor
	/// </summary>
	void ac();
	/// <summary>
	/// move the Cursor to the left by one
	/// </summary>
	void move_cursor_left();
	/// <summary>
	/// move the Cursor to the right by one
	/// </summary>
	void move_cursor_right();
	/// <summary>
	/// move the Cursor up by one
	/// </summary>
	void move_cursor_up();
	/// <summary>
	/// move the Cursor down by one
	/// </summary>
	void move_cursor_down();
private:

	/// <summary>
	/// Node for the tree representing the Equation
	/// </summary>
	struct EquationNode {
		uint8_t* value;
		std::vector<EquationNode*>* children;

		~EquationNode() {
			if (children != nullptr) {
				for (EquationNode* child : *children) delete child;
				delete children;
			}
			if (value != nullptr) delete value;
		}
	};
	/// <summary>
	/// _equation_root_raw Node for the equation, children contains the equation
	/// </summary>
	EquationNode* _equation_root_raw;
	/// <summary>
	/// _equation_root_raw Node for the equation, where parts in brackets are collected in another child
	/// </summary>
	EquationNode* _equation_root_formatted;

	/// <summary>
	/// all the operations that have to be between two values to be evaluated
	/// </summary>
	std::vector<uint8_t> allowedCalculateOperations {
		69, 70, 71, 72, 74, 75, 85, 98, 114, 115, 118, 119, 120, 130, 138, 139, 140, 152, 153, 154, 159, 162, 163, 164
	};

	std::vector<uint8_t> singleBracketOpenKeys{
		74, 114, 115, 118, 119, 120, 138, 139, 140, 152, 153, 154, 160, 161, 162, 163, 164, 190, 191, 192, 193, 194, 195
	};

	/// <summary>
	/// Node Used for the Calculation
	/// </summary>
	struct CalculateNode {
		double* value;
		uint8_t* operation;
		~CalculateNode() {
			if (value != nullptr) delete value;
			if (operation != nullptr) delete operation;
		}
	};

	/// <summary>
	/// the rendered Equation without the Cursor
	/// </summary>
	bitset_2d rendered_equation;
	/// <summary>
	/// the rendered equation with the Cursor
	/// </summary>
	bitset_2d rendered_equation_cursor;
	/// <summary>
	/// has the equation changed since last rendered?
	/// </summary>
	bool equation_changed;
	/// <summary>
	/// bool keeping track of wether to show the cursor or not (in 0.5s intervals)
	/// </summary>
	bool show_cursor;
	/// <summary>
	/// the current Position of the Cursor. Cursor is always displayed between the element it points to and the previous element
	/// </summary>
	std::vector<uint16_t> cursor_index;
	/// <summary>
	/// time since boot at which the cursor last changed its state
	/// </summary>
	uint64_t last_blink_time;

	struct cursorData {
		int64_t x = 0;
		int64_t y = 0;
		uint8_t size = 0;
	};

	CalculateNode* calculate_equation_part(const std::vector<EquationNode*>& equation, Error& error);
	bitset_2d render_equation_part(const std::vector<EquationNode*>& equation, const std::map<uint8_t, bitset_2d>& table,  std::vector<uint16_t> render_index, cursorData& cursor_data, uint32_t& y_origin_ref);
	std::vector<Equation::EquationNode*>* format_equation_part(const std::vector<EquationNode*>* equation, uint32_t& i, bool return_on_closed_bracket);
	EquationNode* format_equation(const EquationNode* equation);
};
