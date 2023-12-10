#include "windows/PaintWindow.h"

// TODO: line tool (hold shift to draw straight lines)
// TODO: better preview (blinking cursor in the correct size; empty when eraser is selected, blinking line when line tool is selected)
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

void PaintWindow::draw(int x, int y, bool value)
{
    for (int i = 0; i < _brush_size; i++) {
        for (int j = 0; j < _brush_size; j++) {
            painted.set_bit(x + i, y + j, value);
        }
    }
}

void PaintWindow::draw_line(int x1, int y1, int x2, int y2, bool value)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (true) {
        draw(x1, y1, value);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
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
	else if (keypress.key_calculator == Chars::KEY_MAP.at("DEL")) {
        erase = !erase;
    }
	else if (keypress.key_calculator == Chars::KEY_MAP.at("1")) {
        if (!line) {
			_line_start[0] = _cursor[0];
            _line_start[1] = _cursor[1];
        } else {
            draw_line(_line_start[0], _line_start[1], _cursor[0], _cursor[1], true);
        }
	    line = !line;
    }
	if (_pen_down && !line) {
        draw(_cursor[0], _cursor[1], !erase);
    }
}