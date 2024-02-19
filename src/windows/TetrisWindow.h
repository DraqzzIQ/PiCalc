#pragma once
#include "datastructs/Bitset2D.h"
#include "utils/Utils.h"
#include "windows/Window.h"

// TODO: Add highscore system
class TetrisWindow: public Window
{
	public:
	TetrisWindow();
	~TetrisWindow();

	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	private:
	Bitset2D _pieces[7] = {
		// # #
		// # #
		Bitset2D(4, 4, { { 0b11110000 }, { 0b11110000 }, { 0b11110000 }, { 0b11110000 } }),
		// #
		// #
		// #
		// #
		Bitset2D(2, 8, { { 0b11111111 }, { 0b11111111 } }),
		//   # #
		// # #
		Bitset2D(6, 4, { { 0b11000000 }, { 0b11000000 }, { 0b11110000 }, { 0b11110000 }, { 0b00110000 }, { 0b00110000 } }),
		// # #
		//   # #
		Bitset2D(6, 4, { { 0b00110000 }, { 0b00110000 }, { 0b11110000 }, { 0b11110000 }, { 0b11000000 }, { 0b11000000 } }),
		// #
		// #
		// # #
		Bitset2D(4, 6, { { 0b11111100 }, { 0b11111100 }, { 0b11000000 }, { 0b11000000 } }),
		//   #
		//   #
		// # #
		Bitset2D(4, 6, { { 0b11000000 }, { 0b11000000 }, { 0b11111100 }, { 0b11111100 } }),
		//   #
		// # # #
		Bitset2D(6, 4, { { 0b11000000 }, { 0b11000000 }, { 0b11110000 }, { 0b11110000 }, { 0b11000000 }, { 0b11000000 } })
	};
	void spawn_piece();
	void move_piece_down();
	void move_piece_left();
	void move_piece_right();
	void rotate_piece();
	bool touching_piece(int8_t offset_x = 0, int8_t offset_y = 0);
	void hold();
	void check_for_lines();

	Bitset2D _board;
	uint64_t _last_update;

	const uint8_t _board_offset = 38;
	const uint8_t _board_width = 20;

	uint16_t _score = 0;
	uint16_t _lines = 0;

	uint8_t _falling_piece_x;
	uint8_t _falling_piece_y;

	Bitset2D _falling_piece;
	Bitset2D _next_piece;
	Bitset2D _hold_piece;
};