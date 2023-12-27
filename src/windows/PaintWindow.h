#pragma once
#include "constant/Graphics.h"
#include "windows/Window.h"
#include "constant/Constants.h"
#include "constant/Chars.h"
#include "utils/Utils.h"
#include <iostream>
#include <stack>

class PaintWindow: public Window
{
	public:
	PaintWindow();
	~PaintWindow();
	Bitset2D update_window();
	void handle_key_down(KeyPress keypress);

	private:
	enum class Tool {
    	LINE,
    	RECTANGLE,
    	CIRCLE,
    	NONE
	};

	static void draw(int x, int y, bool value, int size, Bitset2D& bitset);
	static void draw_line(int x1, int y1, int x2, int y2, bool value, int size, Bitset2D& bitset);
	static void draw_rectangle(int x0, int y0, int x1, int y1, bool value, int size, Bitset2D& bitset);
    static void draw_ellipse(int x0, int y0, int x1, int y1, bool value, int size, Bitset2D& bitset);
	void fill(int x, int y, bool value, Bitset2D& bitset);
	Bitset2D draw_preview(Bitset2D& target);

	Bitset2D painted;
	Bitset2D _rendered_preview;
	Bitset2D _rendered;

	int _cursor[2] = {0, 0};
	bool _pen_down = false;
	int _brush_size = 1;
	bool erase = false;
	int _start_pos[2] = {0, 0};
	int _blink_timer;
	bool preview = true;

	Tool _tool = Tool::NONE;

	Bitset2D history[20];
	int current_history_index = 0;
	std::stack<Bitset2D> redo_stack{};

	int corner_x = 0;
	int corner_y = 0;
};
