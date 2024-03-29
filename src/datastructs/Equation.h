#pragma once
#include "constant/Chars.h"
#include "constant/Constants.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "datastructs/Number.h"
#include "datastructs/NumberParser.h"
#include "utils/Utils.h"


class Equation
{
	public:
	/// <summary>
	/// Construct a new Equation
	/// </summary>
	Equation();
	/// <summary>
	/// create a new Equation from a KEY_SET
	/// </summary>
	Equation(const KEY_SET& equation);
	/// <summary>
	/// delete the Equation and clear allocated Memory
	/// </summary>
	~Equation();

	/// <summary>
	/// set the size of the frame the equation is rendered in
	/// </summary>
	void set_frame_size(uint32_t width, uint32_t height);
	/// <summary>
	/// false: cursor is not shown
	/// true: cursor is blinking
	/// </summary>
	void set_cursor_state(bool active);
	/// <summary>
	/// set the equation to the givcen KEY_SET
	/// </summary>
	void set_key_set(const KEY_SET& equation);
	/// <summary>
	/// return the rendered equation
	/// </summary>
	/// <param name="complete">if true returns the whole equation, otherwise a bitset of the size set by set_frame_size(), containing the part of the equation that the cursor is in</param>
	Bitset2D get_rendered_equation(bool complete = false);
	/// <summary>
	/// returns a const reference to the raw bytes (underlying KEY_SET) of the equation, for example for saving Notes<para/>
	/// IMPORTANT: the result is unuseable after the Equation is deleted
	/// </summary>
	const KEY_SET* get_raw_bytes() const;
	/// <summary>
	/// sets result to the ascii bytes of the equation, for example for Chatgpt and Wolframalpha
	/// </summary>
	std::string get_ascii_bytes(bool english) const;

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
	/// <summary>
	/// handle a keypress: up/down/left/right/del/ac: move cursor; any other key: add it to the equation
	/// </summary>
	void handle_key_down(KEY keypress);

	/// <summary>
	/// links another variable list to this equation, so that it also can be changed in this equation
	/// </summary>
	/// <param name="variables"></param>
	void set_variable_list(std::map<KEY, Number*>* variables);
	/// <summary>
	/// calculate the equation
	/// </summary>
	/// <returns>result</returns>
	Number* to_number(uint16_t settings);

	private:
	/// <summary>
	/// all the operations that have to be between two values to be evaluated
	/// </summary>
	static const KEY_SET _allowed_calculate_operations;
	/// <summary>
	/// all keys that have an opening breacket at the end (which is not automatically closed like logn, including a raw opening bracket)
	/// </summary>
	static const KEY_SET _bracket_keys;
	/// <summary>
	/// when these values are in front of an exponent, no empty-value is added
	/// </summary>
	static const KEY_SET _values_before_exponent;
	/// <summary>
	/// all Symbols that need to be ended by SYMBOL_END
	/// </summary>
	static const KEY_SET _symbols;
	/// <summary>
	/// text representation of the symbols
	/// </summary>
	static const std::map<KEY, std::string> _symbols_text;
	/// <summary>
	/// text representation of the bracket keys
	/// </summary>
	static const std::map<KEY, std::string> _bracket_keys_text;

	/// <summary>
	/// a KEY_SET (vector of Keys) storing the equation
	/// </summary>
	KEY_SET _equation;
	/// <summary>
	/// the current Position of the Cursor in the equation. Cursor is always displayed before the element it points to
	/// </summary>
	uint32_t _cursor_index;

	/// <summary>
	/// stores the position and size of the cursor
	/// </summary>
	struct CursorPositionData {
		int64_t x = 0;
		int64_t y = 0;
		KEY size = 0;
	};
	/// <summary>
	/// stores the position and size of the cursor
	/// </summary>
	CursorPositionData _cursor_data;
	/// <summary>
	/// stores the complete raw rendered equat�on
	/// </summary>
	Bitset2D _rendered_equation;
	/// <summary>
	/// stores the complete raw rendered equat�on with the cursor added
	/// </summary>
	Bitset2D _rendered_equation_cursor;
	/// <summary>
	/// stores the part of the raw equation that is within the frame
	/// </summary>
	Bitset2D _rendered_equation_frame;
	/// <summary>
	/// stores the part of the equation that is within the frame with the cursor added
	/// </summary>
	Bitset2D _rendered_equation_cursor_frame;
	/// <summary>
	/// the index of the symbol of the equation currently being rendered
	/// </summary>
	uint32_t _render_index;
	/// <summary>
	/// stores wether the cursor is blinking or not
	/// </summary>
	bool _show_cursor = true;
	/// <summary>
	/// bool keeping track of wether to show the cursor or not (in 0.5s intervals)
	/// </summary>
	bool _cursor_active = true;
	/// <summary>
	/// time since boot at which the cursor last changed its state
	/// </summary>
	uint64_t _last_blink_time = 0;
	/// <summary>
	/// x coordinate of the top left corner of the frame the equation is rendered in
	/// </summary>
	uint32_t _frame_x = 0;
	/// <summary>
	/// y coordinate of the top left corner of the frame the equation is rendered in
	/// </summary>
	uint32_t _frame_y = 0;
	/// <summary>
	/// width of the frame the equation is rendered in
	/// </summary>
	uint32_t _frame_width = SCREEN_WIDTH;
	/// <summary>
	/// height of the frame the equation is rendered in
	/// </summary>
	uint32_t _frame_height = SCREEN_HEIGHT;
	/// <summary>
	/// index of the equation currently converted to a number
	/// </summary>
	uint32_t _calculate_index;
	/// <summary>
	/// pointer to the list of variables used in the equation
	/// </summary>
	std::map<KEY, Number*>* _variables;
	/// <summary>
	/// settings variable
	/// </summary>
	uint16_t _settings;
	/// <summary>
	/// Node Used for the Calculation
	/// </summary>
	struct CalculateNode {
		Number* value = nullptr;
		uint8_t operation = 0;
		int32_t equation_index = -1;
	};

	/// <summary>
	/// render the equation
	/// </summary>
	void render_equation();
	/// <summary>
	/// renders a subequation with a leading and trailing free column, starting at _render_index, stopping at a closed bracket, a next value char or an end symbol char, uses _render_index as counter
	/// </summary>
	/// <param name="table">Keymap to be used</param>
	/// <param name="y_origin">set to the y origin of the rendered subequation</param>
	/// <param name="cursor_inside">set to true if the cursor is in this subequation, otherwise not changed</param>
	/// <param name="cursor_offset_x">x offset applied to the cursor, if it's in this subequation</param>
	/// <param name="cursor_offset_y">y offset applied to the cursor, if it's in this subequation</param>
	/// <param name="cursor_alignment">0: in reference to y_origin; 1: in reference to the top; 2: in reference to the bottom</param>
	/// <param name="type">0: top level; 1: symbol; 2: bracket;</param>
	/// <returns>the rendered subequation</returns>
	Bitset2D render_equation_part(uint8_t font_height, int32_t& y_origin, bool& cursor_inside, int32_t cursor_offset_x = 0, int32_t cursor_offset_y = 0, uint8_t cursor_alignment = 0, uint8_t type = 1);
	/// <summary>
	/// renders a subequation with a leading and trailing free column, starting at _render_index, stopping at an end symbol char / next value char (if mixed_fraction), uses _render_index as counter
	/// </summary>
	/// <param name="cursor_inside"></param>
	/// <param name="cursor_offset_x"></param>
	/// <param name="mixed_fraction"></param>
	/// <returns></returns>
	Bitset2D render_restricted(uint8_t font_height, FONT* table, bool& cursor_inside, int32_t cursor_offset_x, int8_t cursor_offset_y, bool mixed_fraction);
	/// <summary>
	/// appends the second bitset to the first one with their y_origins aligned
	/// </summary>
	void extend_bitset_left_and_match_y_origin(Bitset2D& bitset, int32_t& y_origin, const Bitset2D& bitset_new, int32_t y_origin_new);
	/// <summary>
	/// returns the equation as a simple string, showing the cursor position and all values of the equation as numbers (KEYs)
	/// </summary>
	std::string to_string_simple() const;

	/// <summary>
	/// add a new child with the given amount of children to the equation at the cursor position
	/// with the option to either add the value before the cursor to the first child, specify tht value of the first child or add the value after the cursor to the 2nd child / 1st child if there is no 2nd child
	/// <param name="mode">
	/// 0: one value, no adding<para/>
	/// 1: one value, add right<para/>
	/// 2: one value, add first_child<para/>
	/// 3: two values, no adding<para/>
	/// 4: two values, add both<para/>
	/// 5: two values, add first_child and right<para/>
	/// 6: three values, add both
	/// </param>
	/// </summary>
	void add_value_raw(KEY value, uint8_t mode, KEY_SET first_child = {});
	/// <summary>
	/// returns the smallest index of the equation that is included in a value starting from the given index - 1 going to the left
	/// </summary>
	uint32_t get_value_end_left(uint32_t index, bool only_decimal);
	/// <summary>
	/// returns the smallest index of the equation that is not included in a value starting from the given index going to the right
	/// </summary>
	uint32_t get_value_end_right(uint32_t index);

	/// <summary>
	/// converts a part of the equation to a number, starting at _calculate_index, stopping at a closed bracket, a next value char or an end symbol char, uses _calculate_index as counter
	/// </summary>
	Number* to_number_part(KEY expected_ending);
};
