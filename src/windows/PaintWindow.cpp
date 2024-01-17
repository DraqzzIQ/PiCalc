#include "windows/PaintWindow.h"

// TODO: add round brush
// TODO: brightness


PaintWindow::PaintWindow()
{
	_painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	_cursor_x = SCREEN_WIDTH / 2;
	_cursor_y = SCREEN_HEIGHT / 2;
	_blink_timer = Utils::us_since_boot();
}

PaintWindow::~PaintWindow() = default;

Bitset2D PaintWindow::update_window()
{
	_draw_preview(_painted).copy(_corner_x, _corner_y, SCREEN_WIDTH, SCREEN_HEIGHT, _rendered);
	return _rendered;
}

Bitset2D PaintWindow::_draw_preview(Bitset2D target)
{
	if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer += 500000;
		_preview = !_preview;
	}

	switch (_tool) {
	case Tool::LINE: _draw_line(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, _preview, _brush_size, target); break;
	case Tool::RECTANGLE: _draw_rectangle(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, _preview, _brush_size, target); break;
	case Tool::CIRCLE: _draw_ellipse(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, _preview, _brush_size, target); break;
	default:
		if (_erase) _draw_rectangle(_cursor_x - _brush_size / 2, _cursor_y - _brush_size / 2, _cursor_x + _brush_size / 2, _cursor_y + _brush_size / 2, _preview, 1, target);
		else _draw(_cursor_x, _cursor_y, _preview, _brush_size, target);
	}
	return target;
}

void PaintWindow::_draw(uint32_t x, uint32_t y, bool value, uint8_t size, Bitset2D& bitset)
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

void PaintWindow::_draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool value, uint8_t size, Bitset2D& bitset)
{
	int dx = x2 > x1 ? x2 - x1 : x1 - x2;
	int dy = y2 > y1 ? y2 - y1 : y1 - y2;
	int8_t sx = (x1 < x2) ? 1 : -1;
	int8_t sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (true) {
		_draw(x1, y1, value, size, bitset);
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

void PaintWindow::_draw_rectangle(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool value, uint8_t size, Bitset2D& bitset)
{
	_draw_line(x0, y0, x1, y0, value, size, bitset); // Top edge
	_draw_line(x0, y1, x1, y1, value, size, bitset); // Bottom edge
	_draw_line(x0, y0, x0, y1, value, size, bitset); // Left edge
	_draw_line(x1, y0, x1, y1, value, size, bitset); // Right edge
}

void PaintWindow::_draw_ellipse(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool value, uint8_t size, Bitset2D& bitset)
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
		_draw(x1, y0, value, size, bitset);
		_draw(x0, y0, value, size, bitset);
		_draw(x0, y1, value, size, bitset);
		_draw(x1, y1, value, size, bitset);
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
		_draw(x0 - 1, y0, value, size, bitset);
		_draw(x1 + 1, y0++, value, size, bitset);
		_draw(x0 - 1, y1, value, size, bitset);
		_draw(x1 + 1, y1--, value, size, bitset);
	}
}

void PaintWindow::_fill(uint32_t x, uint32_t y, bool value, Bitset2D& bitset, int limit)
{
	if (limit <= 0) return;
	if (x >= bitset.width() || y >= bitset.height()) return;
	if (bitset.get_bit(x, y) == value) return;
	bitset.set_bit(x, y, value);
	_fill(x + 1, y, value, bitset, limit - 1);
	_fill(x - 1, y, value, bitset, limit - 1);
	_fill(x, y + 1, value, bitset, limit - 1);
	_fill(x, y - 1, value, bitset, limit - 1);
}

bool PaintWindow::_set_tool(Tool tool)
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

void PaintWindow::_save_to_hist()
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

void PaintWindow::_scroll_left()
{
	if (_corner_x > 0) _corner_x--;
	if (_cursor_x >= corner_x + SCREEN_WIDTH - 1) _cursor_x = _corner_x + SCREEN_WIDTH - 1;
}

void PaintWindow::_scroll_right()
{
	if (_corner_x < _painted.width()) _painted.extend_right(1, false);
	_corner_x++;
	if (_cursor_x <= _corner_x) _cursor_x = _corner_x;
}

void PaintWindow::_scroll_up()
{
	if (_corner_y > 0) _corner_y--;
	if (_cursor_y >= _corner_y + SCREEN_HEIGHT - 1) _cursor_y = _corner_y + SCREEN_HEIGHT - 1;
}

void PaintWindow::_scroll_down()
{
	if (_corner_y + SCREEN_HEIGHT >= _painted.height()) _painted.extend_down(1, false);
	_corner_y++;
	if (_cursor_y <= _corner_y) _cursor_y = _corner_y;
}

bool PaintWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.alpha) {
		switch (keypress.key_raw) {
		case 167: // up
			_scroll_up();
			break;
		case 168: // down
			_scroll_down();
			break;
		case 169: // left
			_scroll_left();
			break;
		case 170: // right
			_scroll_right();
			break;
		}
	} else if (!keypress.shift) {
		switch (keypress.key_raw) {
		case 167: // up
			if (_cursor_y == corner_y) _scroll_up();
			if (_cursor_y > 0) _cursor_y--;
			break;
		case 168: // down
			if (_cursor_y == _corner_y + SCREEN_HEIGHT - 1) _scroll_down();
			_cursor_y++;
			break;
		case 169: // left
			if (_cursor_x == _corner_x) _scroll_left();
			if (_cursor_x > 0) _cursor_x--;
			break;
		case 170: // right
			if (_cursor_x == _corner_x + SCREEN_WIDTH - 1) _scroll_right();
			_cursor_x++;
			break;
		case 73: // =
			_set_tool(Tool::PEN);
			_save_to_hist();
			break;
		case 1: // 1
			if (_set_tool(Tool::LINE)) _draw_line(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			_save_to_hist();
			break;
		case 2: // 2
			if (_set_tool(Tool::RECTANGLE)) _draw_rectangle(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			_save_to_hist();
			break;
		case 3: // 3
			if (_set_tool(Tool::CIRCLE)) _draw_ellipse(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			_save_to_hist();
			break;
		case 4: // 4
			if (_tool == Tool::NONE) _fill(_cursor_x, _cursor_y, !_erase, _painted);
			_save_to_hist();
			break;
		case 126: // AC
			_painted = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
			_save_to_hist();
			break;
		case 125: // DEL
			_erase = !_erase;
			_save_to_hist();
			break;
		case 0: // 0
			_corner_x = 0;
			_corner_y = 0;
			break;
		case 69: // +
			if (_brush_size < 5) _brush_size++;
			break;
		case 70: // -
			if (_brush_size > 1) _brush_size--;
			break;
		case 71: // multiply
			if (_current_history_index > 1) {
				_redo_stack.push(_history[--_current_history_index]);
				_painted = _history[_current_history_index - 1];
			}
			break;
		case 72: // divide
			if (!_redo_stack.empty()) {
				_history[_current_history_index++] = _redo_stack.top();
				_painted = _redo_stack.top();
				_redo_stack.pop();
			}
			break;
		case 128: // ans
			_cursor_x = SCREEN_WIDTH / 2 + corner_x;
			_cursor_y = SCREEN_HEIGHT / 2 + corner_y;
			break;
		case 121: // RCL
			_open_save_menu();
			break;
		case 122: // ENG
			_open_load_menu();
			break;
		}
	}

	if (_tool == Tool::PEN)
		_draw(_cursor_x, _cursor_y, !_erase, _brush_size, _painted);

	return true;
}
void PaintWindow::_open_load_menu()
{
	std::function<void(std::string)> callback = [this](std::string filename)
	{
		_bytes.clear();
		#ifdef PICO
		SDCardController::read_file("paint", filename, &bytes);
		#else
		std::cout << "Reading from file on desktop" << std::endl;
		std::ifstream in_file("paint/" + filename, std::ios::binary);
		{
			if (in_file.is_open()) {
				in_file.seekg(0, std::ios::end);
				_bytes.resize(in_file.tellg());
				in_file.seekg(0, std::ios::beg);
				in_file.read((char*)_bytes.data(), _bytes.size());
				in_file.close();
			} else {
				std::cout << "Failed to open file" << std::endl;
			}
		}
		#endif
		if (_bytes.size() == 0) return;
		_painted = Bitset2D::from_bmp(_bytes);
		_corner_x = 0;
		_corner_y = 0;
		_cursor_x = SCREEN_WIDTH / 2;
		_cursor_y = SCREEN_HEIGHT / 2;
		WindowManager::get_instance()->minimize_window();
	};
	{
		# ifdef PICO
		std::vector<std::string> files = SDCardController::list_dir("paint");
		# else
		std::vector<std::string> files = {};
		for (const auto & entry : std::filesystem::directory_iterator("paint"))
			files.push_back(entry.path().filename().string());
		# endif
		_load_menu.options.clear();
		for (const auto & file : files) {
			_load_menu.options.push_back(new ValueMenuOption<std::string>(file, file, callback));
		}
		WindowManager::get_instance()->add_window(&_load_menu);
		_load_menu.create_menu();
	}
}

void PaintWindow::_open_save_menu()
{
	std::string filename = InputWindow::input("Enter filename: ");
	if (filename.rfind(".bmp") == std::string::npos) {
		filename += ".bmp";
	}
	std::replace(filename.begin(), filename.end(), ' ', '_');
	_bytes = _painted.to_bmp();
#ifdef PICO
	SDCardController::write_file("paint", filename, &_bytes);
#else
	std::cout << "Writing to file on desktop" << std::endl;
	{
		std::ofstream out_file("paint/"+filename, std::ios::binary);
		if (out_file.is_open()) {
			out_file.write((char*)_bytes.data(), _bytes.size());
			out_file.close();
		} else {
			std::cout << "Failed to open file" << std::endl;
		}
	}
#endif
}