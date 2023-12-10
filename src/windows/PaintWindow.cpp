#include "windows/PaintWindow.h"

// TODO: eraser tool
// TODO: line tool (hold shift to draw straight lines)
// TODO: rectangle tool
// TODO: circle tool
// TODO: save/load
// TODO: brightness


PaintWindow::PaintWindow()
{
    painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	_cursor[0] = SCREEN_WIDTH / 2;
	_cursor[1] = SCREEN_HEIGHT / 2;
}

PaintWindow::~PaintWindow() {}

Bitset2D PaintWindow::update_window()
{
	Bitset2D _rendered = painted;
	_rendered.set_bit(_cursor[0], _cursor[1], true);
	return _rendered;
}

void PaintWindow::brush(int x, int y)
{
    for (int i = 0; i < _brush_size; i++) {
        for (int j = 0; j < _brush_size; j++) {
            painted.set_bit(x + i, y + j, true);
        }
    }
}

void PaintWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_calculator == Chars::KEY_MAP.at("up")) {
        _cursor[1]--;
        if (_cursor[1] < 0) _cursor[1] = 0;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("down")) {
        _cursor[1]++;
        if (_cursor[1] >= SCREEN_HEIGHT) _cursor[1] = SCREEN_HEIGHT - 1;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("left")) {
        _cursor[0]--;
        if (_cursor[0] < 0) _cursor[0] = 0;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("right")) {
        _cursor[0]++;
        if (_cursor[0] >= SCREEN_WIDTH) _cursor[0] = SCREEN_WIDTH - 1;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("=")) {
        _pen_down = !_pen_down;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("AC")) {
        painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
    }
	else if (keypress.key_calculator == Chars::KEY_MAP.at("+")) {
	        _brush_size++;
        if (_brush_size > 5) _brush_size = 5;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("-")) {
        _brush_size--;
        if (_brush_size < 1) _brush_size = 1;
    }
	if (_pen_down) {
        brush(_cursor[0], _cursor[1]);
    }
}