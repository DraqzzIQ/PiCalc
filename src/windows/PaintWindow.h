#pragma once
#include "constant/Graphics.h"
#include "windows/Window.h"
#include "constant/Chars.h"
#include "constant/Constants.h"
#include <iostream>

class PaintWindow: public Window
{
	public:
	PaintWindow();
	~PaintWindow();
	Bitset2D update_window();
	void handle_key_down(KeyPress keypress);

	private:
	Bitset2D _rendered;
	int _cursor[2] = {0, 0};
	bool _pen_down = false;
};
