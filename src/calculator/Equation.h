#pragma once
#include "constant/Graphics.h"
#include "keyboard/KeyPress.h"
#include "utils/Utils.h"
#include "windows/Window.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>


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
	/// return the rendered equation
	/// </summary>
	Bitset2D get_rendered_equation();
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

		~EquationNode()
		{
			if (children != nullptr) {
				for (EquationNode* child : *children) delete child;
				delete children;
			}
			if (value != nullptr) delete value;
		}
	};

	/// <summary>
	/// Node Used for the Calculation
	/// </summary>
	struct CalculateNode {
		double* value;
		uint8_t* operation;
		~CalculateNode()
		{
			if (value != nullptr) delete value;
			if (operation != nullptr) delete operation;
		}
	};

	/// <summary>
	/// stores the position and size of the cursor
	/// </summary>
	struct CursorPositionData {
		int64_t x = 0;
		int64_t y = 0;
		uint8_t size = 0;
	};

	/// <summary>
	/// root Node for the equation, children contains the equation
	/// </summary>
	EquationNode* _equation_root;
	/// <summary>
	/// the current Position of the Cursor in the raw equation. Cursor is always displayed between the element it points to and the previous element
	/// </summary>
	std::vector<uint32_t> _cursor_index;
	/// <summary>
	/// the rendered Equation without the Cursor
	/// </summary>
	Bitset2D _rendered_equation;
	/// <summary>
	/// the rendered equation with the Cursor
	/// </summary>
	Bitset2D _rendered_equation_cursor;
	/// <summary>
	/// bool keeping track of wether to show the cursor or not (in 0.5s intervals)
	/// </summary>
	bool _show_cursor;
	/// <summary>
	/// time since boot at which the cursor last changed its state
	/// </summary>
	uint64_t _last_blink_time;
	/// <summary>
	/// all the operations that have to be between two values to be evaluated
	/// </summary>
	std::vector<uint8_t> allowedCalculateOperations{ 69, 70, 71, 72, 74, 75, 85, 98, 114, 115, 118, 119, 120, 130, 138, 139, 140, 152, 153, 154, 159, 162, 163, 164 };
	/// <summary>
	/// all Keys that end with an open rounded bracket
	/// </summary>
	std::vector<uint8_t> singleBracketOpenKeys{ 74, 114, 115, 118, 119, 120, 138, 139, 140, 152, 153, 154, 160, 161, 162, 163, 164, 190, 191, 192, 193, 194, 195 };

	/// <summary>
	/// render the equation
	/// </summary>
	void render_equation();
	/// <summary>
	/// calculates the result of a equation, made for recursion
	/// </summary>
	/// <param name="equation">the equation to be calculated</param>
	/// <param name="error">set to an error type if any occur, else Fine</param>
	/// <returns>Result</returns>
	CalculateNode* calculate_equation_part(const std::vector<EquationNode*>& equation, Error& error);
	/// <summary>
	/// renders an equation, made for recursion
	/// </summary>
	/// <param name="equation">equation to be rendered</param>
	/// <param name="table">the Keymap to be used</param>
	/// <param name="render_index">absolute index of the equation, that ie being rendered</param>
	/// <param name="cursor_data">set to the new cursor Position if the cursor is in the passed equation</param>
	/// <param name="y_origin_ref">y origin of the rendered equation</param>
	/// <returns>the rendered equation</returns>
	Bitset2D render_equation_part(const std::vector<EquationNode*>& equation, const std::map<uint8_t, Bitset2D>& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint32_t start = 0, uint32_t end = -1);
	/// <summary>
	/// formats an equation part by collecting all parts in brackets in a child, made for recursion
	/// </summary>
	/// <param name="equation">equation to be formatted</param>
	/// <param name="i">index to start at</param>
	/// <param name="cursor_index_curr">current cursor index</param>
	/// <param name="return_on_closed_bracket">set to true if it should return as soon as a closed bracket occurs</param>
	/// <returns>the formatted equation</returns>
	std::vector<Equation::EquationNode*>* format_equation_part(const std::vector<EquationNode*>* equation, uint32_t& i, bool return_on_closed_bracket);
};
