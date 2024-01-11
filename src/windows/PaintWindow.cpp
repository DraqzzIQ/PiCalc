#include "windows/PaintWindow.h"

// TODO: make paint window scrollable
// TODO: add round brush
// TODO: save/load
// TODO: brightness


PaintWindow::PaintWindow()
{
	_painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	_cursor[0] = SCREEN_WIDTH / 2;
	_cursor[1] = SCREEN_HEIGHT / 2;
	_blink_timer = Utils::us_since_boot();
}

PaintWindow::~PaintWindow() = default;

Bitset2D PaintWindow::update_window()
{
	draw_preview(_painted).copy(corner_x, corner_y, SCREEN_WIDTH, SCREEN_HEIGHT, _rendered);
	return _rendered;
}

Bitset2D PaintWindow::draw_preview(Bitset2D target)
{
	if (Utils::us_since_boot() > _blink_timer + 200000) {
		_blink_timer += 200000;
		preview = !preview;
	}

	switch (_tool) {
	case Tool::PEN:
		if (_erase) draw_rectangle(_cursor[0] - _brush_size / 2, _cursor[1] - _brush_size / 2, _cursor[0] + _brush_size / 2, _cursor[1] + _brush_size / 2, preview, 1, target);
		else draw(_cursor[0], _cursor[1], preview, _brush_size, target);
		break;
	case Tool::LINE: draw_line(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], preview, _brush_size, target); break;
	case Tool::RECTANGLE: draw_rectangle(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], preview, _brush_size, target); break;
	case Tool::CIRCLE: draw_ellipse(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], preview, _brush_size, target); break;
	default: draw(_cursor[0], _cursor[1], preview, 1, target);
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

bool PaintWindow::set_tool(Tool tool)
{
	if (_tool == Tool::NONE) {
		_start_pos[0] = _cursor[0];
		_start_pos[1] = _cursor[1];
		_tool = tool;
		return false;
	}
	_tool = Tool::NONE;
	return true;
}

void PaintWindow::save_to_hist()
{
	if (current_history_index < 1 || _painted != history[current_history_index - 1]) {
		if (current_history_index < 20) {
			history[current_history_index++] = _painted;
			std::stack<Bitset2D>().swap(redo_stack);
		} else {
			for (int i = 0; i < 18; i++) {
				history[i] = history[i + 1];
			}
			history[19] = _painted;
			std::stack<Bitset2D>().swap(redo_stack);
		}
	}
}

bool PaintWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.alpha) {
		switch (keypress.key_raw) {
		case 167: // up
			if (corner_y > 0) corner_y--;
			break;
		case 168: // down
			corner_y++;
			break;
		case 169: // left
			if (corner_x > 0) corner_x--;
			break;
		case 170: // right
			corner_x++;
			break;
		}
	} else if (!keypress.shift) {
		switch (keypress.key_raw) {
		case 167: // up
			if (_cursor[1] > 0) _cursor[1]--;
			if (_cursor[1] < corner_y && corner_y > 0) corner_y--;
			break;
		case 168: // down
			_cursor[1]++;
			if (_cursor[1] >= SCREEN_HEIGHT) corner_y++;
			break;
		case 169: // left
			if (_cursor[0] > 0) _cursor[0]--;
			if (_cursor[0] < corner_x && corner_x > 0) corner_x--;
			break;
		case 170: // right
			_cursor[0]++;
			if (_cursor[0] >= SCREEN_WIDTH) corner_x++;
			break;
		case 73: // =
			set_tool(Tool::PEN);
			save_to_hist();
			break;
		case 1: // 1
			if (set_tool(Tool::LINE)) draw_line(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], true, _brush_size, _painted);
			save_to_hist();
			break;
		case 2: // 2
			if (set_tool(Tool::RECTANGLE)) draw_rectangle(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], true, _brush_size, _painted);
			save_to_hist();
			break;
		case 3: // 3
			if (set_tool(Tool::CIRCLE)) draw_ellipse(_start_pos[0], _start_pos[1], _cursor[0], _cursor[1], true, _brush_size, _painted);
			save_to_hist();
			break;
		case 4: // 4
			if (_tool == Tool::NONE) fill(_cursor[0], _cursor[1], !_erase, _painted);
			save_to_hist();
			break;
		case 126: // AC
			_painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
			save_to_hist();
			break;
		case 125: // DEL
			_erase = !_erase;
			save_to_hist();
			break;
		case 0: // 0
			corner_x = 0;
			corner_y = 0;
			break;
		case 69: // +
			if (_brush_size < 5) _brush_size++;
			break;
		case 70: // -
			if (_brush_size > 0) _brush_size--;
			break;
		case 71: // multiply
			if (current_history_index > 1) {
				redo_stack.push(history[--current_history_index]);
				_painted = history[current_history_index - 1];
			}
			break;
		case 72: // divide
			if (!redo_stack.empty()) {
				history[current_history_index++] = redo_stack.top();
				_painted = redo_stack.top();
				redo_stack.pop();
			}
			break;
		}
	}

	if (corner_x + SCREEN_WIDTH > _painted.width())
		_painted.extend_right(corner_x + SCREEN_WIDTH - _painted.width(), false);
	if (corner_y + SCREEN_HEIGHT > _painted.height())
		_painted.extend_down(corner_y + SCREEN_HEIGHT - _painted.height(), false);
	if (_tool == Tool::PEN)
		draw(_cursor[0], _cursor[1], !_erase, _brush_size, _painted);

	return true;
}