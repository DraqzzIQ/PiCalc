#pragma once
#include "calculator/Equation.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "windows/Window.h"
#include <iostream>

class PongWindow: public Window
{
	public:
	PongWindow();
	~PongWindow();
	Bitset2D update_window();
	bool handle_key_down(KeyPress keypress);

	private:
	enum class Menu {
		ONLINE,
		PLATFORM,
		DIFFICULTY,
		GAME
	};
	Menu _menu = Menu::ONLINE;
	uint8_t _paddle_width = 0;
	uint8_t _rpaddle_pos = (SCREEN_HEIGHT - _paddle_width) / 2;
	uint8_t _lpaddle_pos = (SCREEN_HEIGHT - _paddle_width) / 2;
	uint8_t _ball_x = SCREEN_WIDTH / 2;
	uint8_t _ball_y = SCREEN_HEIGHT / 2;
	int8_t _ball_vx = 10;
	int8_t _ball_vy = 0;
	/// <summary>
	/// right to left:
	/// 0, 1: difficulty (0-3)
	/// 2: 0=offline, 1=online
	/// 3: 0=platform direction change, 1=platform position change
	/// </summary>
	uint8_t _settings;

	Bitset2D _window;
};
