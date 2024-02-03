#pragma once
#include "constant/Chars.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "utils/Utils.h"
#include "windows/Window.h"
#include <iostream>

/// <summary>
/// Window for playing Pong<para/>
/// IMPORTANT: each pixel on the screen are 64 pixels in this Window to achieve more precise movement
/// controls for Pico: 4 / 1 / divide / -
/// controls for PC: up / down / e / d
/// </summary>
class PongWindow: public Window
{
	public:
	PongWindow();
	~PongWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;
	bool handle_key_up(KeyPress keypress) override;

	private:
	enum class Menu {
		ONLINE,
		DURATION,
		PLATFORM,
		DIFFICULTY,
		GAME,
		WIN
	};
	Menu _menu = Menu::ONLINE;

	/// <summary>
	/// is the game online?
	/// </summary>
	bool _online = false;
	/// <summary>
	/// are the platforms in easy mode (they only move when a key is pressed) or
	/// hard mode (they move always and a keypress toggles the direction of the platform)?
	/// </summary>
	bool _platform_easy = false;
	/// <summary>
	/// height of the paddle
	/// </summary>
	uint16_t _paddle_height = 0;
	/// <summary>
	/// lowest allowed position of the paddles
	/// </summary>
	uint16_t _paddle_max_pos = 0;
	/// <summary>
	/// speed of the paddles
	/// </summary>
	uint16_t _paddle_speed = 0;
	/// <summary>
	/// speed of the ball at the beginning of the game
	/// </summary>
	int16_t _start_ball_vx = 0;
	/// <summary>
	/// points needed to win the game
	/// </summary>
	int16_t _win_points = 0;
	/// <summary>
	/// maximum x velocity the ball can move at
	/// </summary>
	int16_t _max_ball_vx = 0;
	/// <summary>
	/// maximum y velocity the ball can move at
	/// </summary>
	int16_t _max_ball_vy = 0;

	/// <summary>
	/// score of the right player
	/// </summary>
	uint16_t _rscore = 0;
	/// <summary>
	/// score of the left player
	/// </summary>
	uint16_t _lscore = 0;
	/// <summary>
	/// position of the right paddle
	/// </summary>
	int16_t _rpaddle_pos = 0;
	/// <summary>
	/// position of the left paddle
	/// </summary>
	int16_t _lpaddle_pos = 0;
	/// <summary>
	/// movement of the right paddle (-1 = up, 0 = none, 1 = down)
	/// </summary>
	int8_t _rpaddle_v = 0;
	/// <summary>
	/// movement of the left paddle (-1 = up, 0 = none, 1 = down)
	/// </summary>
	int8_t _lpaddle_v = 0;
	/// <summary>
	/// x position of the ball
	/// </summary>
	int16_t _ball_x = 0;
	/// <summary>
	/// y position of the ball
	/// </summary>
	int16_t _ball_y = 0;
	/// <summary>
	/// steps per frame in x direction
	/// </summary>
	int16_t _ball_vx = 0;
	/// <summary>
	/// steps per frame in y direction
	/// </summary>
	int16_t _ball_vy = 0;

	void start_game();
	void move_paddles();
	void move_ball();
	void render_game();
};
