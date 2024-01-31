#include "PongWindow.h"

PongWindow::PongWindow()
{
	_menu = Menu::ONLINE;
	_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Online?", false);
	_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "0: no", false);
	_window.put_chars(0, 17, Graphics::SYMBOLS_6_HIGH, "1: yes", false);
}

PongWindow::~PongWindow() {}

void PongWindow::update_window()
{
	if (_menu == Menu::GAME) {
		move_paddles();
		move_ball();
		render_game();
	}
}

bool PongWindow::handle_key_down(KeyPress keypress)
{
	switch (_menu) {
	case Menu::ONLINE:
		if (keypress.key_raw == '0') _online = false;
		else if (keypress.key_raw == '1') _online = true;
		else return false;
		_menu = Menu::DURATION;
		clear_window();
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Duration? ", false);
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "0:S(6)", false);
		_window.put_chars(48, 9, Graphics::SYMBOLS_6_HIGH, "1:M(11)", false);
		_window.put_chars(0, 17, Graphics::SYMBOLS_6_HIGH, "2:L(16)", false);
		_window.put_chars(48, 17, Graphics::SYMBOLS_6_HIGH, "3:XL(21)", false);
		_window.put_chars(0, 25, Graphics::SYMBOLS_6_HIGH, "4:endless", false);
		return true;
	case Menu::DURATION:
		if (keypress.key_raw == '0') _win_points = 6;
		else if (keypress.key_raw == '1') _win_points = 11;
		else if (keypress.key_raw == '2') _win_points = 16;
		else if (keypress.key_raw == '3') _win_points = 21;
		else if (keypress.key_raw == '4') _win_points = 65535;
		else return false;
		_menu = Menu::PLATFORM;
		clear_window();
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Platform Mode?", false);
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "0: easy", false);
		_window.put_chars(0, 17, Graphics::SYMBOLS_6_HIGH, "1: hard", false);
		return true;
	case Menu::PLATFORM:
		if (keypress.key_raw == '0') _platform_easy = true;
		else if (keypress.key_raw == '1') _platform_easy = false;
		else return false;
		_menu = Menu::DIFFICULTY;
		clear_window();
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Difficulty? ", false);
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "0-9", false);
		return true;
	case Menu::DIFFICULTY:
		if ((keypress.key_raw -= 48) < 10) {
			_paddle_height = 512 - (keypress.key_raw / 3) * 64;
			_paddle_speed = 32 + keypress.key_raw * 2;
			_start_ball_vx = 32 + keypress.key_raw * 4;
			_max_ball_vx = 64 + keypress.key_raw * 2;
			_max_ball_vy = 32 + keypress.key_raw * 3;
			start_game();
			return true;
		}
		return false;
	case Menu::GAME:
#ifdef PICO
		if (_platform_easy) {
			if (keypress.key_raw == '4') _lpaddle_v = -1;
			else if (keypress.key_raw == '1') _lpaddle_v = 1;
			else if (keypress.key_raw == 247) _rpaddle_v = -1;
			else if (keypress.key_raw == '-') _rpaddle_v = 1;
			else return false;
		} else {
			if (keypress.key_raw == '4' || keypress.key_raw == '1') _lpaddle_v *= -1;
			else if (keypress.key_raw == 247 || keypress.key_raw == '-') _rpaddle_v *= -1;
			else return false;
		}
#else
		if (_platform_easy) {
			if (keypress.key_keyboard == 'w') _lpaddle_v = -1;
			else if (keypress.key_keyboard == 's') _lpaddle_v = 1;
			else if (keypress.key_keyboard == 3) _rpaddle_v = -1;
			else if (keypress.key_keyboard == 4) _rpaddle_v = 1;
			else return false;
		} else {
			if (keypress.key_keyboard == 'w' || keypress.key_keyboard == 's') _lpaddle_v *= -1;
			else if (keypress.key_keyboard == 3 || keypress.key_keyboard == 4) _rpaddle_v *= -1;
			else return false;
		}
#endif
		return true;
	case Menu::WIN:
		if (keypress.key_raw == '0') start_game();
		else if (keypress.key_raw == '1') {
			_menu = Menu::ONLINE;
			clear_window();
			_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Online?", false);
			_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "0: no", false);
			_window.put_chars(0, 17, Graphics::SYMBOLS_6_HIGH, "1: yes", false);
		} else return false;
		return true;
	}
}

bool PongWindow::handle_key_up(KeyPress keypress)
{
	if (_menu == Menu::GAME) {
		if (!_platform_easy) return true;
#ifdef PICO
		if (keypress.key_raw == '4' || keypress.key_raw == '1') _lpaddle_v = 0;
		else if (keypress.key_raw == 247 || keypress.key_raw == '-') _rpaddle_v = 0;
		else return false;
#else
		if (keypress.key_keyboard == 'w' || keypress.key_keyboard == 's') _lpaddle_v = 0;
		else if (keypress.key_keyboard == 3 || keypress.key_keyboard == 4) _rpaddle_v = 0;
		else return false;
#endif
		return true;
	} else return false;
}

void PongWindow::start_game()
{
	_menu = Menu::GAME;
	_lscore = 0;
	_rscore = 0;
	_paddle_max_pos = SCREEN_HEIGHT * 64 - _paddle_height;
	_rpaddle_pos = _paddle_max_pos / 2;
	_lpaddle_pos = _paddle_max_pos / 2;
	_lpaddle_v = _platform_easy ? 0 : 1;
	_rpaddle_v = _platform_easy ? 0 : 1;
	_ball_x = SCREEN_WIDTH * 32;
	_ball_y = SCREEN_HEIGHT * 32;
	_ball_vx = _start_ball_vx;
	_ball_vy = ((Utils::us_since_boot() % 7) - 2) * 8;
}

void PongWindow::move_paddles()
{
	// move the paddles
	_lpaddle_pos += _lpaddle_v * _paddle_speed;
	_rpaddle_pos += _rpaddle_v * _paddle_speed;

	// check the left paddle for collisions
	if (_lpaddle_pos < 0) {
		if (_platform_easy) {
			_lpaddle_pos = 0;
			_lpaddle_v = 0;
		} else {
			_lpaddle_pos = 0;
		}
	} else if (_lpaddle_pos >= _paddle_max_pos) {
		if (_platform_easy) {
			_lpaddle_pos = _paddle_max_pos;
			_lpaddle_v = 0;
		} else {
			_lpaddle_pos = _paddle_max_pos;
		}
	}

	// check the right paddle for collisions
	if (_rpaddle_pos < 0) {
		if (_platform_easy) {
			_rpaddle_pos = 0;
			_rpaddle_v = 0;
		} else {
			_rpaddle_pos = 0;
		}
	} else if (_rpaddle_pos >= _paddle_max_pos) {
		if (_platform_easy) {
			_rpaddle_pos = _paddle_max_pos;
			_rpaddle_v = 0;
		} else {
			_rpaddle_pos = _paddle_max_pos;
		}
	}
}

void PongWindow::move_ball()
{
	// move the ball
	_ball_x += _ball_vx;
	_ball_y += _ball_vy;

	// check for collisions with the top and bottom of the screen
	if (_ball_y < 0) {
		_ball_y = -_ball_y;
		_ball_vy = -_ball_vy;
	} else if (_ball_y >= SCREEN_HEIGHT * 64) {
		_ball_y = SCREEN_HEIGHT * 128 - _ball_y - 1;
		_ball_vy = -_ball_vy;
	}

	// check for collisions with the paddles and the sides of the screen, on every collision the ball gets faster
	if (_ball_x < 64) {
		if (_ball_y >= _lpaddle_pos && _ball_y < _lpaddle_pos + _paddle_height) {
			_ball_x = -_ball_x;
			_ball_vx = -_ball_vx + 2;
			_ball_vy += ((Utils::us_since_boot() % 7) - 2) * 2;
			_ball_vy += _lpaddle_v * _paddle_speed / 2;
		} else {
			_rscore++;
			_ball_x = SCREEN_WIDTH * 32;
			_ball_y = SCREEN_HEIGHT * 32;
			_ball_vx = _start_ball_vx;
			_ball_vy = ((Utils::us_since_boot() % 7) - 2) * 8;
		}
	} else if (_ball_x >= (SCREEN_WIDTH - 1) * 64) {
		if (_ball_y >= _rpaddle_pos && _ball_y < _rpaddle_pos + _paddle_height) {
			_ball_x = (SCREEN_WIDTH - 1) * 128 - _ball_x;
			_ball_vx = -_ball_vx - 2;
			_ball_vy += ((Utils::us_since_boot() % 7) - 2) * 2;
			_ball_vy += _rpaddle_v * _paddle_speed / 2;
		} else {
			_lscore++;
			_ball_x = SCREEN_WIDTH * 32;
			_ball_y = SCREEN_HEIGHT * 32;
			_ball_vx = -_start_ball_vx;
			_ball_vy = ((Utils::us_since_boot() % 7) - 2) * 8;
		}
	}
	if (_ball_vx > _max_ball_vx) _ball_vx = _max_ball_vx;
	else if (_ball_vx < -_max_ball_vx) _ball_vx = -_max_ball_vx;
	if (_ball_vy > _max_ball_vy) _ball_vy = _max_ball_vy;
	else if (_ball_vy < -_max_ball_vy) _ball_vy = -_max_ball_vy;
}

void PongWindow::render_game()
{
	clear_window();

	// show whether someone won, otherwise draw the ball
	if (_rscore == _win_points) {
		_menu = Menu::WIN;
		_window.put_chars(18, 9, Graphics::SYMBOLS_6_HIGH, "Right won!", false);
		_window.put_chars(18, 17, Graphics::SYMBOLS_6_HIGH, "0: restart", false);
		_window.put_chars(27, 25, Graphics::SYMBOLS_6_HIGH, "1: menu", false);
	} else if (_lscore == _win_points) {
		_menu = Menu::WIN;
		_window.put_chars(21, 9, Graphics::SYMBOLS_6_HIGH, "Left won!", false);
		_window.put_chars(18, 17, Graphics::SYMBOLS_6_HIGH, "0: restart", false);
		_window.put_chars(27, 25, Graphics::SYMBOLS_6_HIGH, "1: menu", false);
	} else _window.set_bit(_ball_x / 64, _ball_y / 64 + 1, true);

	// draw the paddles
	_window.draw_vertical_line(0, _lpaddle_pos / 64 + 1, _paddle_height / 64, true);
	_window.draw_vertical_line(SCREEN_WIDTH - 1, _rpaddle_pos / 64 + 1, _paddle_height / 64, true);

	// draw the left score
	KEY_SET score_key_set = KEY_SET();
	uint8_t score_width = 0;
	uint8_t score = _lscore;
	if (score == 0) {
		score_key_set.push_back('0');
		score_width += 4;
	}
	while (score > 0) {
		score_key_set.push_back((score % 10) + 48);
		score /= 10;
		score_width += 4;
	}
	std::reverse(score_key_set.begin(), score_key_set.end());
	_window.put_chars(48 - score_width, 1, Graphics::SYMBOLS_5_HIGH, score_key_set, false);

	// draw the right score
	score_key_set.clear();
	score = _rscore;
	if (score == 0) score_key_set.push_back('0');
	while (score > 0) {
		score_key_set.push_back((score % 10) + 48);
		score /= 10;
	}
	std::reverse(score_key_set.begin(), score_key_set.end());
	_window.put_chars(50, 1, Graphics::SYMBOLS_5_HIGH, score_key_set, false);
}