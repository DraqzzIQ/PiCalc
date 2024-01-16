#include "windows/PaintWindow.h"

// TODO: save/load
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
	draw_preview(_painted).copy(_corner_x, _corner_y, SCREEN_WIDTH, SCREEN_HEIGHT, _rendered);
	return _rendered;
}

Bitset2D PaintWindow::draw_preview(Bitset2D target)
{
	if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer += 500000;
		preview = !preview;
	}

	switch (_tool) {
	case Tool::LINE: draw_line(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, preview, _brush_size, target); break;
	case Tool::RECTANGLE: draw_rectangle(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, preview, _brush_size, target); break;
	case Tool::CIRCLE: draw_ellipse(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, preview, _brush_size, target); break;
	default:
		if (_erase) draw_rectangle(_cursor_x - _brush_size / 2, _cursor_y - _brush_size / 2, _cursor_x + _brush_size / 2, _cursor_y + _brush_size / 2, preview, 1, target);
		else draw(_cursor_x, _cursor_y, preview, _brush_size, target);
	}
	return target;
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

void PaintWindow::scroll_left()
{
	if (_corner_x > 0) _corner_x--;
	if (_cursor_x >= corner_x + SCREEN_WIDTH - 1) _cursor_x = _corner_x + SCREEN_WIDTH - 1;
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
		case 167: // up
			scroll_up();
			break;
		case 168: // down
			scroll_down();
			break;
		case 169: // left
			scroll_left();
			break;
		case 170: // right
			scroll_right();
			break;
		}
	} else if (!keypress.shift) {
		switch (keypress.key_raw) {
		case 167: // up
			if (_cursor_y == corner_y) scroll_up();
			if (_cursor_y > 0) _cursor_y--;
			break;
		case 168: // down
			if (_cursor_y == _corner_y + SCREEN_HEIGHT - 1) scroll_down();
			_cursor_y++;
			break;
		case 169: // left
			if (_cursor_x == _corner_x) scroll_left();
			if (_cursor_x > 0) _cursor_x--;
			break;
		case 170: // right
			if (_cursor_x == _corner_x + SCREEN_WIDTH - 1) scroll_right();
			_cursor_x++;
			break;
		case 73: // =
			set_tool(Tool::PEN);
			save_to_hist();
			break;
		case 1: // 1
			if (set_tool(Tool::LINE)) draw_line(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			save_to_hist();
			break;
		case 2: // 2
			if (set_tool(Tool::RECTANGLE)) draw_rectangle(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			save_to_hist();
			break;
		case 3: // 3
			if (set_tool(Tool::CIRCLE)) draw_ellipse(_start_pos_x, _start_pos_y, _cursor_x, _cursor_y, true, _brush_size, _painted);
			save_to_hist();
			break;
		case 4: // 4
			if (_tool == Tool::NONE) fill(_cursor_x, _cursor_y, !_erase, _painted);
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
		case 128: // ans
			_cursor_x = SCREEN_WIDTH / 2 + corner_x;
			_cursor_y = SCREEN_HEIGHT / 2 + corner_y;
			break;
		case 121: // RCL
			// openSaveMenu();
			bytes = _painted.to_bmp();
			// TODO: open window to name file
			#ifdef PICO
				SDCardController::write_file("paint", "test.bmp", &bytes);
			#else
				std::cout << "Writing to file on desktop" << std::endl;
				{
				std::ofstream out_file("paint/test.bmp", std::ios::binary);
				if (out_file.is_open()) {
					out_file.write((char*)bytes.data(), bytes.size());
					out_file.close();
				} else {
					std::cout << "Failed to open file" << std::endl;
				}
				}
			#endif
			break;
		case 122: // ENG
			openLoadMenu();
			break;
		}
	}

	if (_tool == Tool::PEN)
		draw(_cursor_x, _cursor_y, !_erase, _brush_size, _painted);

	return true;
}
void PaintWindow::openLoadMenu()
{
	std::function<void(std::string)> callback = [this](std::string filename)
	{
		bytes.clear();
		#ifdef PICO
		SDCardController::read_file("paint", filename, &bytes);
		#else
		std::cout << "Reading from file on desktop" << std::endl;
		std::ifstream in_file("paint/" + filename, std::ios::binary);
		{
			if (in_file.is_open()) {
				in_file.seekg(0, std::ios::end);
				bytes.resize(in_file.tellg());
				in_file.seekg(0, std::ios::beg);
				in_file.read((char*)bytes.data(), bytes.size());
				in_file.close();
			} else {
				std::cout << "Failed to open file" << std::endl;
			}
		}
		#endif
		if (bytes.size() == 0) return;
		_painted = Bitset2D::from_bmp(bytes);
		_corner_x = 0;
		_corner_y = 0;
		_cursor_x = SCREEN_WIDTH / 2;
		_cursor_y = SCREEN_HEIGHT / 2;
		WindowManager::get_instance()->minimize_window();
	};
	{
		# ifdef PICO
		std::vector<string> files = SDCardController::list_dir("paint");
		# else
		std::vector<std::string> files = {};
		for (const auto & entry : std::filesystem::directory_iterator("paint"))
			files.push_back(entry.path().filename().string());
		# endif
		load_menu.options.clear();
		for (const auto & file : files) {
			load_menu.options.push_back(new ValueMenuOption<std::string>(file, file, callback));
		}
		WindowManager::get_instance()->add_window(&load_menu);
		load_menu.create_menu();
	}
}

void PaintWindow::openSaveMenu()
{
	auto input_window = InputWindow();
	input_window.set_prompt("Enter filename:");
	// WindowManager::get_instance()->add_window(&input_window);
}