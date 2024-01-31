#include "windows/TetrisWindow.h"

TetrisWindow::TetrisWindow()
{
	_board = Bitset2D(_board_width, 31, false);
	_last_update = Utils::us_since_boot();
	srand(Utils::us_since_boot());
	_next_piece = _pieces[rand() % 7];
	spawn_piece();
}

TetrisWindow::~TetrisWindow()
{
}

void TetrisWindow::update_window()
{
	clear_window();

	_window.put_chars(3, 1, Graphics::SYMBOLS_6_HIGH, "Hold:", true);
	_window.set(14, 8, _hold_piece, true);

	_window.put_chars(2, 16, Graphics::SYMBOLS_6_HIGH, "Score:", true);
	_window.put_chars(3, 24, Graphics::SYMBOLS_6_HIGH, std::to_string(_score), true);

	_window.set(_board_offset - 2, 1, Bitset2D(2, 31, true), true);
	_window.set(_board_offset, 1, _board, true);
	_window.set(_board_offset + _board_width, 1, Bitset2D(2, 31, true), true);

	_window.put_chars(_board_offset + _board_width + 5, 1, Graphics::SYMBOLS_6_HIGH, "Next:", true);
	_window.set(_board_offset + _board_width + 16, 8, _next_piece, true);

	_window.put_chars(_board_offset + _board_width + 3, 16, Graphics::SYMBOLS_6_HIGH, "Lines:", true);
	_window.put_chars(_board_offset + _board_width + 4, 24, Graphics::SYMBOLS_6_HIGH, std::to_string(_lines), true);


	for (uint8_t i = 0; i < _falling_piece.width(); i++) {
		for (uint8_t j = 0; j < _falling_piece.height(); j++) {
			if (_falling_piece.get_bit(i, j)) {
				_window.set_bit(_falling_piece_x + i, _falling_piece_y + j, true);
			}
		}
	}

	if (Utils::us_since_boot() - _last_update > 1000000) {
		move_piece_down();
		_last_update = Utils::us_since_boot();
	}
}

bool TetrisWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("left")) {
		move_piece_left();
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("right")) {
		move_piece_right();
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("down")) {
		_score += 1;
		move_piece_down();
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("=")) {
		hold();
	} else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("SHIFT")) {
		rotate_piece();
	}

	return true;
}

void TetrisWindow::spawn_piece()
{
	_falling_piece = _next_piece;
	uint8_t offset = 48 - _falling_piece.width() / 2;
	if (offset % 2 == 1) offset--;
	_falling_piece_x = offset;
	_falling_piece_y = 1;
	if (touching_piece()) {
		// game over
		_board = Bitset2D(_board_width, 31, false);
		_hold_piece.clear();
		_score = 0;
		_lines = 0;
	}

	int index = rand() % 7;
	_next_piece = _pieces[index];
}

void TetrisWindow::move_piece_down()
{
	if (_falling_piece_y + _falling_piece.height() < _board.height() && !touching_piece(0, 1)) {
		_falling_piece_y += 2;
		return;
	}

	uint8_t local_x = _falling_piece_x - _board_offset;

	for (uint8_t i = 0; i < _falling_piece.width(); i++) {
		for (uint8_t j = 0; j < _falling_piece.height(); j++) {
			if (_falling_piece.get_bit(i, j)) {
				_board.set_bit(local_x + i, _falling_piece_y + j, true);
			}
		}
	}

	check_for_lines();
	spawn_piece();
}

void TetrisWindow::check_for_lines()
{
	uint8_t lines = 0;

	for (uint8_t i = 0; i < _board.height(); i += 2) {
		bool line = true;
		for (uint8_t j = 0; j < _board.width(); j++) {
			if (!_board.get_bit(j, i)) {
				line = false;
				break;
			}
		}


		if (line) {
			lines++;
			for (uint8_t j = i; j > 1; j -= 1) {
				for (uint8_t k = 0; k < _board.width(); k++) {
					_board.set_bit(k, j, _board.get_bit(k, j - 2));
				}
			}
		}
	}

	_lines += lines;
	switch (lines) {
	case 1:
		_score += 100;
		break;
	case 2:
		_score += 300;
		break;
	case 3:
		_score += 500;
		break;
	case 4:
		_score += 800;
		break;
	default:
		break;
	}
}

bool TetrisWindow::touching_piece(int8_t offset_x, int8_t offset_y)
{
	uint8_t local_x = _falling_piece_x - _board_offset;

	for (uint8_t i = 0; i < _falling_piece.width(); i++) {
		for (uint8_t j = 0; j < _falling_piece.height(); j++) {
			if (_falling_piece.get_bit(i, j) && _board.get_bit(local_x + i + offset_x, _falling_piece_y + j + offset_y)) {
				return true;
			}
		}
	}

	return false;
}

void TetrisWindow::hold()
{
	if (_hold_piece.width() == 0) {
		_hold_piece = _falling_piece;
		spawn_piece();
		return;
	}

	Bitset2D temp = _falling_piece;
	_falling_piece = _hold_piece;
	_hold_piece = temp;
}

void TetrisWindow::move_piece_left()
{
	if (_falling_piece_x > _board_offset && !touching_piece(-1, 0)) _falling_piece_x -= 2;
}

void TetrisWindow::move_piece_right()
{
	if (_falling_piece_x + _falling_piece.width() < _board_offset + _board_width && !touching_piece(1, 0)) _falling_piece_x += 2;
}

void TetrisWindow::rotate_piece()
{
	uint8_t m = _falling_piece.height();
	uint8_t n = _falling_piece.width();

	Bitset2D new_piece = Bitset2D(m, n, false);

	for (uint8_t i = 0; i < n; i++) {
		for (uint8_t j = 0; j < m; j++) {
			new_piece.set_bit(m - j - 1, i, _falling_piece.get_bit(i, j));
		}
	}


	int8_t x_offset = (_falling_piece.width() - new_piece.width()) / 2;
	if (x_offset % 2 == 1)
		x_offset++;

	if (x_offset + _falling_piece_x < _board_offset)
		_falling_piece_x = _board_offset;
	else if (_falling_piece_x + new_piece.width() + x_offset > _board_offset + _board_width)
		_falling_piece_x = _board_offset + _board_width - new_piece.width();
	else _falling_piece_x += x_offset;

	if (_falling_piece_x % 2 == 1)
		_falling_piece_x--;

	_falling_piece = new_piece;
}