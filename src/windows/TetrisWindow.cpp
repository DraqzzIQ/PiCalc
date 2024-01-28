#include "windows/TetrisWindow.h"

TetrisWindow::TetrisWindow()
{
	board = Bitset2D(20, 32, true);
}

TetrisWindow::~TetrisWindow()
{
}

Frame TetrisWindow::update_window()
{
	clear_window();

	add_to_window(board, 38, 0);

	return Frame(_window, _screen_symbols);
}

bool TetrisWindow::handle_key_down(KeyPress keypress)
{
	return true;
}