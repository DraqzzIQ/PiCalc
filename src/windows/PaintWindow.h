#pragma once
#include "constant/Graphics.h"
#include "windows/Window.h"
#include "constant/Constants.h"
#include "constant/Chars.h"
#include <iostream>

class PaintWindow: public Window
{
	public:
	PaintWindow();
	~PaintWindow();
	Bitset2D update_window();
	void handle_key_down(KeyPress keypress);

	private:
	void draw(int x, int y, bool value);
	Bitset2D painted;
	Bitset2D _rendered;
	int _cursor[2] = {0, 0};
	bool _pen_down = false;
	int _brush_size = 1;
	bool erase = false;
};
