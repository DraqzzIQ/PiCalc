#include "datastructs/Bitset2D.h"
#include "utils/Utils.h"
#include "windows/Window.h"

class TetrisWindow: public Window
{
	public:
	TetrisWindow();
	~TetrisWindow();

	Frame update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	private:
	Bitset2D board;
	Bitset2D peices[7] = {
		Bitset2D(2, 2, { { 0b11000000 }, { 0b11000000 } }),
		Bitset2D(1, 4, { { 0b11110000 } }),
		Bitset2D(3, 2, { { 0b10000000 }, { 0b11000000 }, { 0b01000000 } }),
		Bitset2D(3, 2, { { 0b01000000 }, { 0b11000000 }, { 0b10000000 } }),
		Bitset2D(2, 3, { { 0b11100000 }, { 0b10000000 } }),
		Bitset2D(2, 3, { { 0b10000000 }, { 0b11100000 } }),
		Bitset2D(3, 3, { { 0b01000000 }, { 0b11000000 }, { 0b01000000 } })
	};
	void spawn_piece();
	void move_piece_down();
	void move_piece_left();
	void move_piece_right();
	void rotate_piece();
	uint64_t _last_update;
};