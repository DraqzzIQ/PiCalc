#pragma once
#include "constant/Error.h"
#include "constant/Graphics.h"
// #include "datastructs/Number.h"
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
	/// links another variable list to this equation, so that it also can be changed in this equation
	/// </summary>
	/// <param name="variables"></param>
	// void set_variable_list(std::vector<Number>* variables);

	/// <summary>
	/// set the size of the frame the equation is rendered in
	/// </summary>
	/// <param name="height"></param>
	/// <param name="width"></param>
	void set_frame_size(uint32_t width, uint32_t height);
	/// <summary>
	/// return the rendered equation
	/// </summary>
	Bitset2D get_rendered_equation(bool complete = false);
	/// <summary>
	/// add a Value to the equation at the current Cursor position
	/// </summary>
	/// <param name="keypress">Char to add</param>
	void add_value(uint8_t keypress);

	/// <summary>
	/// calculate the equation
	/// </summary>
	/// <returns>result</returns>
	// Number calculate_equation(const std::vector<double> variables);

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
	/// all the operations that have to be between two values to be evaluated
	/// </summary>
	static const std::vector<uint8_t> _allowed_calculate_operations;
	/// <summary>
	/// all Keys that end with an open rounded bracket
	/// </summary>
	static const std::vector<uint8_t> _single_bracket_open_keys;
	/// <summary>
	/// when these values are in front of an exponent, no empty-value is added
	/// </summary>
	static const std::vector<uint8_t> _values_before_exponent;
	/// <summary>
	/// all symbols that need one or more children
	/// </summary>
	static const std::vector<uint8_t> _symbols;

	/// <summary>
	/// Node Used for the Calculation
	/// </summary>
	// struct CalculateNode {
	//	Number value = Number();
	//	uint8_t operation = 95;
	//	int32_t equation_index = -1;
	// };

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
	std::vector<uint8_t> _equation;
	/// <summary>
	/// the current Position of the Cursor in the raw equation. Cursor is always displayed between the element it points to and the previous element
	/// </summary>
	uint32_t _cursor_index;
	/// <summary>
	/// stores the position and size of the cursor
	/// </summary>
	CursorPositionData _cursor_data;
	/// <summary>
	/// variables storing different variants of the rendered equation
	/// </summary>
	Bitset2D _rendered_equation;
	Bitset2D _rendered_equation_frame;
	Bitset2D _rendered_equation_cursor;
	Bitset2D _rendered_equation_cursor_frame;
	/// <summary>
	/// the index of the symbol of the equation currently being rendered
	/// </summary>
	uint32_t _render_index;
	/// <summary>
	/// bool keeping track of wether to show the cursor or not (in 0.5s intervals)
	/// </summary>
	bool _show_cursor;
	/// <summary>
	/// time since boot at which the cursor last changed its state
	/// </summary>
	uint64_t _last_blink_time;
	uint32_t _frame_x = 0;
	uint32_t _frame_y = 0;
	uint32_t _frame_width = SCREEN_WIDTH;
	uint32_t _frame_height = SCREEN_HEIGHT;
	// std::vector<Number>* _variables = nullptr;


	std::string to_string_simple() const;
	/// <summary>
	/// render the equation
	/// </summary>
	void render_equation();
	/// <summary>
	/// appenbds the second bitset to the first one with their y_origins aligned
	/// </summary>
	void extend_bitset_left_and_match_y_origin(Bitset2D& bitset, int32_t& y_origin, const Bitset2D& bitset_new, int32_t y_origin_new);

	/// <summary>
	/// calculates the result of a equation, made for recursion
	/// </summary>
	/// <param name="equation">the equation to be calculated</param>
	/// <param name="error">set to an error type if any occur, else Fine</param>
	/// <returns>Result</returns>
	// Number calculate_equation_part(std::vector<EquationNode*>& equation, std::vector<uint32_t> calculate_index, uint32_t& i, bool stop_on_closed_bracket = false);

	/// <summary>
	/// renders a subequation with a leading and trailing free column, starting at _render_index, stopping at a closed bracket, a next value char or an end symbol char, uses _render_index as counter
	/// </summary>
	/// <param name="table">Keymap to be used</param>
	/// <param name="y_origin">set to the y origin of the rendered subequation</param>
	/// <param name="cursor_offset_x">x offset applied to the cursor, if it's in this subequation</param>
	/// <param name="cursor_offset_y">y offset applied to the cursor, if it's in this subequation</param>
	/// <param name="cursor_alignment">0: in reference to y_origin; 1: in reference to the top; 2: in reference to the bottom</param>
	/// <param name="top_level">if true, throws an error if a closed bracket is there without an opening bracket</param>
	/// <returns>the rendered subequation</returns>
	Bitset2D render_equation_part(FONT& table, int32_t& y_origin, int8_t cursor_offset_x = 0, int8_t cursor_offset_y = 0, uint8_t cursor_alignment = 0, bool bracket = false);
	/// <summary>
	/// add a new child with the given value and amount of children to the equation at the cursor position
	/// with the option to either add the value before the cursor to the first child or specify tht value of the first child
	/// </summary>
	void add_value_raw(uint8_t value, uint8_t child_cnt, bool add_value_to_first_child = false, std::vector<uint8_t> first_child = {});
	/// <summary>
	/// returns true, if value is in vector
	/// </summary>
	static bool in_vector(uint8_t value, const std::vector<uint8_t>& vector);
};
