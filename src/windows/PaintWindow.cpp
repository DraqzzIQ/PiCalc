#include "windows/PaintWindow.h"

// TODO: insead of bool for each tool, use enum
// TODO: add round brush
// TODO: undo/redo
// TODO: save/load
// TODO: brightness


PaintWindow::PaintWindow()
{
    painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	_cursor[0] = SCREEN_WIDTH / 2;
	_cursor[1] = SCREEN_HEIGHT / 2;
	_blink_timer = Utils::us_since_boot();
}

PaintWindow::~PaintWindow() {}

Bitset2D PaintWindow::update_window()
{
	Bitset2D _rendered = painted;
	_rendered = draw_preview(_rendered);
	return _rendered;
}

Bitset2D PaintWindow::draw_preview(Bitset2D& _rendered)
{
    if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer += 500000;
	    preview = !preview;
    }
    if (line) {
        draw_line(_line_start[0], _line_start[1], _cursor[0], _cursor[1], preview, _brush_size, _rendered);
    } else if (erase) {
        draw_rectangle(_cursor[0]-_brush_size/2, _cursor[1]-_brush_size/2, _cursor[0]+_brush_size/2, _cursor[1]+_brush_size/2, preview, 1, _rendered);
    } else if (rectangle) {
        draw_rectangle(_rectangle_start[0], _rectangle_start[1], _cursor[0], _cursor[1], preview, _brush_size, _rendered);
    } else if (circle) {
        draw_ellipse(_circle_start[0], _circle_start[1], _cursor[0], _cursor[1], preview, _brush_size, _rendered);
    }
	else {
        draw(_cursor[0], _cursor[1], preview, _brush_size, _rendered);
    }
    return _rendered;
}

void PaintWindow::draw(int x, int y, bool value, int size, Bitset2D& bitset)
{
    int half_brush = size / 2;
    for (int i = -half_brush; i <= half_brush; i++) {
        for (int j = -half_brush; j <= half_brush; j++) {
            if (x + i >= 0 && x + i < SCREEN_WIDTH && y + j >= 0 && y + j < SCREEN_HEIGHT) {
                bitset.set_bit(x + i, y + j, value);
            }
        }
    }
}

void PaintWindow::draw_line(int x1, int y1, int x2, int y2, bool value, int size, Bitset2D& bitset)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (true) {
        draw(x1, y1, value, size, bitset);
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

void PaintWindow::draw_rectangle(int x0, int y0, int x1, int y1, bool value, int size, Bitset2D& bitset)
{
    draw_line(x0, y0, x1, y0, value, size, bitset); // Top edge
    draw_line(x0, y1, x1, y1, value, size, bitset); // Bottom edge
    draw_line(x0, y0, x0, y1, value, size, bitset); // Left edge
    draw_line(x1, y0, x1, y1, value, size, bitset); // Right edge
}

void PaintWindow::draw_ellipse(int x0, int y0, int x1, int y1, bool value, int size, Bitset2D& bitset)
{
    int a = abs(x1 - x0);
    int b = abs(y1 - y0);
    int b1 = b & 1;
    long dx = 4 * (1 - a) * b * b;
    long dy = 4 * (b1 + 1) * a * a;
    long err = dx + dy + b1 * a * a;

    if (x0 > x1) { x0 = x1; x1 += a; }
    if (y0 > y1) y0 = y1;
    y0 += (b + 1) / 2;
    y1 = y0 - b1;
    a *= 8 * a;
    b1 = 8 * b * b;

    do {
        draw(x1, y0, value, size, bitset);
        draw(x0, y0, value, size, bitset);
        draw(x0, y1, value, size, bitset);
        draw(x1, y1, value, size, bitset);
        int e2 = 2 * err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }
        if (e2 >= dx || 2 * err > dy) { x0++; x1--; err += dx += b1; }
    } while (x0 <= x1);

    while (y0 - y1 <= b) {
        draw(x0 - 1, y0, value, size, bitset);
        draw(x1 + 1, y0++, value, size, bitset);
        draw(x0 - 1, y1, value, size, bitset);
        draw(x1 + 1, y1--, value, size, bitset);
    }
}

void PaintWindow::fill(int x, int y, bool value, Bitset2D& bitset)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    if (bitset.get_bit(x, y) == value) return;
    bitset.set_bit(x, y, value);
    fill(x + 1, y, value, bitset);
    fill(x - 1, y, value, bitset);
    fill(x, y + 1, value, bitset);
    fill(x, y - 1, value, bitset);
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
			rectangle = false;
			circle = false;
        } else {
            draw_line(_line_start[0], _line_start[1], _cursor[0], _cursor[1], true, _brush_size, painted);
        }
	    line = !line;
    }
	else if (keypress.key_calculator == Chars::KEY_MAP.at("2")) {
		if (!rectangle) {
			_rectangle_start[0] = _cursor[0];
            _rectangle_start[1] = _cursor[1];
			line = false;
			circle = false;
        } else {
            draw_rectangle(_rectangle_start[0], _rectangle_start[1], _cursor[0], _cursor[1], true, _brush_size, painted);
        }
        rectangle = !rectangle;
	}
	else if (keypress.key_calculator == Chars::KEY_MAP.at("3")) {
        if (!circle) {
            _circle_start[0] = _cursor[0];
            _circle_start[1] = _cursor[1];
			rectangle = false;
			line = false;
        } else {
            draw_ellipse(_circle_start[0], _circle_start[1], _cursor[0], _cursor[1], true, _brush_size, painted);
        }
        circle = !circle;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at("4")) {
        fill(_cursor[0], _cursor[1], !erase, painted);
    }
	if (_pen_down && !line && !rectangle && !circle) {
        draw(_cursor[0], _cursor[1], !erase, _brush_size, painted);
    }
}