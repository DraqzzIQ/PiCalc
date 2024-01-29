#include "windows/TetrisWindow.h"

TetrisWindow::TetrisWindow()
{
	board = Bitset2D(20, 32, false);
	_last_update = Utils::us_since_boot();
	srand(Utils::us_since_boot());
	spawn_piece();
}

TetrisWindow::~TetrisWindow()
{
}

Frame TetrisWindow::update_window()
{
	clear_window();

	add_to_window(Bitset2D(1, 32, true), 37, 0);
	add_to_window(board, 38, 0);
	add_to_window(Bitset2D(1, 32, true), 59, 0);

	if (Utils::us_since_boot() - _last_update > 1000000) {
		move_piece_down();
		_last_update = Utils::us_since_boot();
	}

	return Frame(_window, _screen_symbols);
}

bool TetrisWindow::handle_key_down(KeyPress keypress)
{
	return true;
}

void TetrisWindow::spawn_piece()
{
	int index = rand() % 7;
	Bitset2D piece = peices[index];
	board.insert_x(0, piece);
}

void TetrisWindow::move_piece_down()
{
}

void TetrisWindow::move_piece_left()
{
}

void TetrisWindow::move_piece_right()
{
}

void TetrisWindow::rotate_piece()
{
}