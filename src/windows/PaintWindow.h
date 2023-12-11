#pragma once
#include "constant/Graphics.h"
#include "windows/Window.h"
#include "constant/Constants.h"
#include "constant/Chars.h"
#include "utils/Utils.h"
#include <iostream>

class PaintWindow: public Window
{
	public:
	PaintWindow();
	~PaintWindow();
	Bitset2D update_window();
	void handle_key_down(KeyPress keypress);

	private:
	void draw(int x, int y, bool value, int size, Bitset2D& bitset);
	void draw_line(int x1, int y1, int x2, int y2, bool value, int size, Bitset2D& bitset);
	void draw_rectangle(int x0, int y0, int x1, int y1, bool value, int size, Bitset2D& bitset);
	Bitset2D draw_preview(Bitset2D& _rendered);
	Bitset2D painted;
	Bitset2D _rendered;
	int _cursor[2] = {0, 0};
	bool _pen_down = false;
	int _brush_size = 1;
	bool erase = false;
    bool line = false;
	bool rectangle = false;
	int _line_start[2] = {0, 0};
	int _rectangle_start[2] = {0, 0};
	int _blink_timer = 0;
	bool preview = true;
};
