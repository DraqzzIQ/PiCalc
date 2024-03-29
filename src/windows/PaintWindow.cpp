#include "windows/PaintWindow.h"
#include "PaintWindow.h"

// TODO: add round brush
// TODO: brightness
// TODO: show tool in screen_symbols


PaintWindow::PaintWindow()
{
	_painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	_cursor_x = SCREEN_WIDTH / 2;
	_cursor_y = SCREEN_HEIGHT / 2;
	_blink_timer = Utils::us_since_boot();
	_frame.corner_y = 0;
}

PaintWindow::~PaintWindow() = default;

void PaintWindow::update_window()
{
	_window = _painted;

	if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer = Utils::us_since_boot();
		_preview = !_preview;
	}

	switch (_tool) {
	case Tool::LINE: draw_line(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, _preview, _brush_size, _window); break;
	case Tool::RECTANGLE: draw_rectangle(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, _preview, _brush_size, _window); break;
	case Tool::CIRCLE: draw_ellipse(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, _preview, _brush_size, _window); break;
	default:
		if (_erase) draw_rectangle(_cursor_x - _brush_size / 2, _cursor_y - _brush_size / 2, _cursor_x + _brush_size / 2, _cursor_y + _brush_size / 2, _preview, 1, _window);
		else draw(_cursor_x, _cursor_y, _preview, _brush_size, _window);
	}
}

void PaintWindow::draw(uint32_t x, uint32_t y, bool value, uint8_t size, Bitset2D& bitset)
{
	int32_t x_start = x - size / 2;
	int32_t y_start = y - size / 2;
	uint32_t x_end = x + (size + 1) / 2;
	uint32_t y_end = y + (size + 1) / 2;

	if (x_start < 0) x_start = 0;
	if (y_start < 0) y_start = 0;
	if (x_end > bitset.width()) x_end = bitset.width() - 1;
	if (y_end > bitset.height()) y_end = bitset.height() - 1;

	for (; x_start < x_end; x_start++) {
		for (uint32_t i = y_start; i < y_end; i++) {
			bitset.set_bit(x_start, i, value);
		}
	}
}

void PaintWindow::draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool value, uint8_t size, Bitset2D& bitset)
{
	int dx = x2 > x1 ? x2 - x1 : x1 - x2;
	int dy = y2 > y1 ? y2 - y1 : y1 - y2;
	int8_t sx = (x1 < x2) ? 1 : -1;
	int8_t sy = (y1 < y2) ? 1 : -1;
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

void PaintWindow::draw_rectangle(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool value, uint8_t size, Bitset2D& bitset)
{
	draw_line(x0, y0, x1, y0, value, size, bitset); // Top edge
	draw_line(x0, y1, x1, y1, value, size, bitset); // Bottom edge
	draw_line(x0, y0, x0, y1, value, size, bitset); // Left edge
	draw_line(x1, y0, x1, y1, value, size, bitset); // Right edge
}

void PaintWindow::draw_ellipse(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool value, uint8_t size, Bitset2D& bitset)
{
	uint32_t a = x1 > x0 ? x1 - x0 : x0 - x1;
	uint32_t b = y1 > y0 ? y1 - y0 : y0 - y1;
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

void PaintWindow::fill(uint32_t x, uint32_t y, bool value, Bitset2D& bitset, int limit)
{
	if (limit <= 0) return;
	if (x >= bitset.width() || y >= bitset.height()) return;
	if (bitset.get_bit(x, y) == value) return;
	bitset.set_bit(x, y, value);
	fill(x + 1, y, value, bitset, limit - 1);
	fill(x - 1, y, value, bitset, limit - 1);
	fill(x, y + 1, value, bitset, limit - 1);
	fill(x, y - 1, value, bitset, limit - 1);
}

bool PaintWindow::set_tool(Tool tool)
{
	if (_tool == Tool::NONE) {
		_start_pos_x = _cursor_x;
		_start_pos_y = _cursor_y;
		_tool = tool;
		return false;
	}
	_tool = Tool::NONE;
	return true;
}

void PaintWindow::save_to_hist()
{
	if (_current_history_index < 1 || _painted != _history[_current_history_index - 1]) {
		if (_current_history_index < 20) {
			_history[_current_history_index++] = _painted;
			std::stack<Bitset2D>().swap(_redo_stack);
		} else {
			for (int i = 0; i < 18; i++) {
				_history[i] = _history[i + 1];
			}
			_history[19] = _painted;
			std::stack<Bitset2D>().swap(_redo_stack);
		}
	}
}

void PaintWindow::scroll_left()
{
	if (_corner_x > 0) _corner_x--;
	if (_cursor_x >= _corner_x + SCREEN_WIDTH - 1) _cursor_x = _corner_x + SCREEN_WIDTH - 1;
}

void PaintWindow::scroll_right()
{
	if (_corner_x < _painted.width()) _painted.extend_right(1, false);
	_corner_x++;
	if (_cursor_x <= _corner_x) _cursor_x = _corner_x;
}

void PaintWindow::scroll_up()
{
	if (_corner_y > 0) _corner_y--;
	if (_cursor_y >= _corner_y + SCREEN_HEIGHT - 1) _cursor_y = _corner_y + SCREEN_HEIGHT - 1;
}

void PaintWindow::scroll_down()
{
	if (_corner_y + SCREEN_HEIGHT >= _painted.height()) _painted.extend_down(1, false);
	_corner_y++;
	if (_cursor_y <= _corner_y) _cursor_y = _corner_y;
}

bool PaintWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.alpha) {
		switch (keypress.key_raw) {
		case KEY_UP: // up
			scroll_up();
			break;
		case KEY_DOWN: // down
			scroll_down();
			break;
		case KEY_LEFT: // left
			scroll_left();
			break;
		case KEY_RIGHT: // right
			scroll_right();
			break;
		}
	} else if (!keypress.shift) {
		switch (keypress.key_raw) {
		case KEY_UP: // up
			if (_cursor_y == _corner_y) scroll_up();
			if (_cursor_y > 0) _cursor_y--;
			break;
		case KEY_DOWN: // down
			if (_cursor_y == _corner_y + SCREEN_HEIGHT - 1) scroll_down();
			_cursor_y++;
			break;
		case KEY_LEFT: // left
			if (_cursor_x == _corner_x) scroll_left();
			if (_cursor_x > 0) _cursor_x--;
			break;
		case KEY_RIGHT: // right
			if (_cursor_x == _corner_x + SCREEN_WIDTH - 1) scroll_right();
			_cursor_x++;
			break;
		case '=':
			set_tool(Tool::PEN);
			save_to_hist();
			break;
		case '1':
			if (set_tool(Tool::LINE)) draw_line(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			save_to_hist();
			break;
		case '2':
			if (set_tool(Tool::RECTANGLE)) draw_rectangle(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			save_to_hist();
			break;
		case '3':
			if (set_tool(Tool::CIRCLE)) draw_ellipse(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			save_to_hist();
			break;
		case '4':
			if (_tool == Tool::NONE) fill(_cursor_x, _cursor_y, !_erase, _painted);
			save_to_hist();
			break;
		case KEY_AC: // AC
			_painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
			save_to_hist();
			break;
		case KEY_DEL: // DEL
			_erase = !_erase;
			save_to_hist();
			break;
		case '0':
			_corner_x = 0;
			_corner_y = 0;
			break;
		case '+':
			if (_brush_size < 5) _brush_size++;
			break;
		case '-':
			if (_brush_size > 1) _brush_size--;
			break;
		case KEY_MULTIPLY: // multiply
			if (_current_history_index > 1) {
				_redo_stack.push(_history[--_current_history_index]);
				_painted = _history[_current_history_index - 1];
			}
			break;
		case KEY_DIVIDE: // divide
			if (!_redo_stack.empty()) {
				_history[_current_history_index++] = _redo_stack.top();
				_painted = _redo_stack.top();
				_redo_stack.pop();
			}
			break;
		case KEY_ANS: // ans
			_cursor_x = SCREEN_WIDTH / 2 + _corner_x;
			_cursor_y = SCREEN_HEIGHT / 2 + _corner_y;
			break;
		case KEY_RCL: // RCL
			open_save_menu();
			break;
		case KEY_ENG: // ENG
			open_load_menu();
			break;
		}
	}

	if (_tool == Tool::PEN)
		draw(_cursor_x, _cursor_y, !_erase, _brush_size, _painted);

	return true;
}
void PaintWindow::open_load_menu()
{
	FileSelectWindow::select_file("paint", [this](std::string filename) {
		KEY_SET bytes;
		IOController::read_file("paint", filename, &bytes);
		_painted.from_bmp(bytes);
		_corner_x = 0;
		_corner_y = 0;
		_cursor_x = SCREEN_WIDTH / 2;
		_cursor_y = SCREEN_HEIGHT / 2;
	});
}

void PaintWindow::open_save_menu()
{
	InputWindow::input("Enter Filename:", [this](std::string& filename) {
		if (filename.rfind(".bmp") == std::string::npos) filename += ".bmp";
		std::replace(filename.begin(), filename.end(), ' ', '_');
		KEY_SET bytes;
		_painted.to_bmp(bytes);
		IOController::write_file("paint", filename, &bytes);
	});
}