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
	enum class Error { MATH_ERROR,
		               PUFFER_ERROR,
		               SYNTAX_ERROR,
		               ARGUMENT_ERROR,
		               STORAGE_ERROR,
		               TIME_ERROR,
		               FINE };
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
		uint8_t value = 95;
		std::vector<EquationNode*> children = std::vector<EquationNode*>();

		~EquationNode()
		{
			for (EquationNode* child : children) delete child;
		}
	};

	/// <summary>
	/// Node Used for the Calculation
	/// </summary>
	struct CalculateNode {
		double value;
		uint8_t operation = 95;
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
	std::vector<uint8_t> _allowed_calculate_operations{ 69, 70, 71, 72, 74, 75, 85, 98, 114, 115, 116, 118, 119, 120, 130, 138, 139, 140, 152, 153, 154, 159, 162, 163, 164 };
	/// <summary>
	/// all Keys that end with an open rounded bracket
	/// </summary>
	std::vector<uint8_t> _single_bracket_open_keys{ 74, 109, 114, 115, 118, 119, 120, 138, 139, 140, 152, 153, 154, 160, 161, 162, 163, 164, 190, 191, 192, 193, 194, 195 };

	/// <summary>
	/// render the equation
	/// </summary>
	void render_equation();
	/// <summary>
	/// appenbds the second bitset to the first one with their y_origins aligned
	/// </summary>
	void extend_bitset_left_and_match_y_origin(Bitset2D& bitset, int32_t& y_origin, Bitset2D& bitset_new, int32_t y_origin_new);
	/// <summary>
	/// calculates the result of a equation, made for recursion
	/// </summary>
	/// <param name="equation">the equation to be calculated</param>
	/// <param name="error">set to an error type if any occur, else Fine</param>
	/// <returns>Result</returns>
	CalculateNode calculate_equation_part(const std::vector<EquationNode*>& equation, Error& error, std::vector<uint32_t> calculate_index, uint32_t& i, bool stop_on_closed_bracket = false);
	/// <summary>
	/// renders an equation, made for recursion
	/// </summary>
	/// <param name="equation">equation to be rendered</param>
	/// <param name="table">the Keymap to be used</param>
	/// <param name="render_index">absolute index of the equation, that ie being rendered</param>
	/// <param name="cursor_data">set to the new cursor Position if the cursor is in the passed equation</param>
	/// <param name="y_origin_ref">y origin of the rendered equation</param>
	/// <returns>the rendered equation</returns>
	Bitset2D render_equation_part(const std::vector<EquationNode*>& equation, FONT& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint32_t& start_index, bool stop_on_closed_bracket = false);
	/// <summary>
	///
	/// </summary>
	Bitset2D render_subequation(const std::vector<EquationNode*>& equation, uint8_t child_index, FONT& table, std::vector<uint32_t> render_index, CursorPositionData& cursor_data, uint32_t& y_origin_ref, uint8_t& child_index_cursor, int32_t cursor_offset_x, int32_t cursor_offset_y);
	/// <summary>
	/// add a new child with the given value and amount of children to the equation at the cursor position
	/// with the option to either add the value before the cursor to the first child or specify tht value of the first child
	/// </summary>
	void add_value_raw(uint8_t value, uint8_t child_cnt, bool add_value_to_first_child = false, std::vector<uint8_t> first_child = {});
};
