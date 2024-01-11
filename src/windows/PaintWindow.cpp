#include "windows/PaintWindow.h"

// TODO: make paint window scrollable
// TODO: add round brush
// TODO: save/load
// TODO: brightness


PaintWindow::PaintWindow()
{
	painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	_cursor[0] = SCREEN_WIDTH / 2;
	_cursor[1] = SCREEN_HEIGHT / 2;
	_blink_timer = Utils::us_since_boot();
}

PaintWindow::~PaintWindow() = default;

Bitset2D PaintWindow::update_window()
{
	_rendered_preview = painted;
	_rendered_preview = draw_preview(_rendered_preview);
	_rendered_preview.copy(corner_x, corner_y, SCREEN_WIDTH, SCREEN_HEIGHT, _rendered);
	return _rendered;
}

Bitset2D PaintWindow::draw_preview(Bitset2D& target)
{
	using enum PaintWindow::Tool;
	if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer += 500000;
		preview = !preview;
	}
	if (_tool == LINE) {
		draw_line(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], preview, _brush_size, target);
	} else if (_tool == RECTANGLE) {
		draw_rectangle(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], preview, _brush_size, target);
	} else if (_tool == CIRCLE) {
		draw_ellipse(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], preview, _brush_size, target);
	} else if (erase) {
		draw_rectangle(_cursor[0] - _brush_size / 2, _cursor[1] - _brush_size / 2, _cursor[0] + _brush_size / 2, _cursor[1] + _brush_size / 2, preview, 1, target);
	} else {
		draw(_cursor[0], _cursor[1], preview, _brush_size, target);
	}
	return target;
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

	if (x0 > x1) {
		x0 = x1;
		x1 += a;
	}
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
		if (e2 <= dy) {
			y0++;
			y1--;
			err += dy += a;
		}
		if (e2 >= dx || 2 * err > dy) {
			x0++;
			x1--;
			err += dx += b1;
		}
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

bool PaintWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("0")) {
		corner_x = 0;
		corner_y = 0;
		return true;
	}

	if (keypress.key_raw == 169 && keypress.alpha) {
		if (corner_x > 0) {
			corner_x--;
		}
		return true;
	}
	if (keypress.key_raw == 170 && keypress.alpha) {
		corner_x++;
		return true;
	}
	if (keypress.key_raw == 167 && keypress.alpha) {
		if (corner_y > 0) {
			corner_y--;
		}
		return true;
	}
	if (keypress.key_raw == 168 && keypress.alpha) {
		corner_y++;
		return true;
	}

	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("up")) {
		if (_cursor[1] > 0) {
			_cursor[1]--;
		}
		if (_cursor[1] < corner_y && corner_y > 0) {
			corner_y--;
		}
	}
	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("down")) {
		_cursor[1]++;
		if (_cursor[1] >= SCREEN_HEIGHT) {
			corner_y++;
		}
	}
	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("left")) {
		if (_cursor[0] > 0) {
			_cursor[0]--;
		}
		if (_cursor[0] < corner_x && corner_x > 0) {
			corner_x--;
		}
	}
	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("right")) {
		_cursor[0]++;
		if (_cursor[0] >= SCREEN_WIDTH) {
			corner_x++;
		}
	}

	if (corner_x + SCREEN_WIDTH > painted.width()) {
		painted.extend_right(corner_x + SCREEN_WIDTH - painted.width(), false);
	}
	if (corner_y + SCREEN_HEIGHT > painted.height()) {
		painted.extend_down(corner_y + SCREEN_HEIGHT - painted.height(), false);
	}

	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("=")) {
		_pen_down = !_pen_down;
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("AC")) {
		painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("+")) {
		_brush_size++;
		if (_brush_size > 5) _brush_size = 5;
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("-")) {
		_brush_size--;
		if (_brush_size < 1) _brush_size = 1;
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("DEL")) {
		erase = !erase;
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("1")) {
		using enum PaintWindow::Tool;
		if (_tool == NONE) {
			_start_pos[0] = _cursor[0];
			_start_pos[1] = _cursor[1];
			_tool = LINE;
		} else {
			draw_line(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], true, _brush_size, painted);
			_tool = NONE;
		}
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("2")) {
		using enum PaintWindow::Tool;
		if (_tool == NONE) {
			_start_pos[0] = _cursor[0];
			_start_pos[1] = _cursor[1];
			_tool = RECTANGLE;
		} else {
			draw_rectangle(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], true, _brush_size, painted);
			_tool = NONE;
		}
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("3")) {
		using enum PaintWindow::Tool;
		if (_tool == NONE) {
			_start_pos[0] = _cursor[0];
			_start_pos[1] = _cursor[1];
			_tool = CIRCLE;
		} else {
			draw_ellipse(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], true, _brush_size, painted);
			_tool = NONE;
		}
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("4")) {
		fill(_cursor[0], _cursor[1], !erase, painted);
	}


	if (_pen_down && _tool == Tool::NONE) {
		draw(_cursor[0], _cursor[1], !erase, _brush_size, painted);
	}


	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("4") ||
	    keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("3") ||
	    keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("2") ||
	    keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("1") ||
	    keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("DEL") ||
	    keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("AC") ||
	    keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("=")) {
		if (current_history_index < 1 || painted != history[current_history_index - 1]) {
			if (current_history_index < 20) {
				history[current_history_index++] = painted;
				std::stack<Bitset2D>().swap(redo_stack);
			} else {
				for (int i = 0; i < 18; i++) {
					history[i] = history[i + 1];
				}
				history[19] = painted;
				std::stack<Bitset2D>().swap(redo_stack);
			}
		}
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("multiply")) { // Undo operation
		if (current_history_index > 1) {
			redo_stack.push(history[--current_history_index]);
			painted = history[current_history_index - 1];
		}
	} else if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("divide")) { // Redo operation
		if (!redo_stack.empty()) {
			history[current_history_index++] = redo_stack.top();
			painted = redo_stack.top();
			redo_stack.pop();
		}
	}
	std::cout << "Bitset size: " << painted.width() << " x " << painted.height() << std::endl;

	return true;
}