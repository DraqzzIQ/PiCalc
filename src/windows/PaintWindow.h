#pragma once
#include "constant/Chars.h"
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "utils/Utils.h"
#include "windows/Window.h"
#include <iostream>
#include <stack>

class PaintWindow: public Window
{
	public:
	PaintWindow();
	~PaintWindow();
	Bitset2D update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	private:
	enum class Tool {
		PEN,
		LINE,
		RECTANGLE,
		CIRCLE,
		NONE
	};
	using Tool = PaintWindow::Tool;
	Tool _tool = Tool::NONE;
	bool _erase = false;

	static void draw(uint32_t x, uint32_t y, bool value, uint8_t size, Bitset2D& bitset);
	static void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool value, uint8_t size, Bitset2D& bitset);
	static void draw_rectangle(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool value, uint8_t size, Bitset2D& bitset);
	static void draw_ellipse(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool value, uint8_t size, Bitset2D& bitset);
	void fill(uint32_t x, uint32_t y, bool value, Bitset2D& bitset);
	bool set_tool(Tool tool);
	void save_to_hist();
	Bitset2D draw_preview(Bitset2D target);

	Bitset2D _painted;
	Bitset2D _rendered;

	uint32_t _corner_x = 0;
	uint32_t _corner_y = 0;
	uint32_t _cursor_x = 0;
	uint32_t _cursor_y = 0;
	uint32_t _start_pos_x = 0;
	uint32_t _start_pos_y = 0;
	uint8_t _brush_size = 1;
	uint64_t _blink_timer;
	bool preview = true;

	uint8_t current_history_index = 0;
	Bitset2D history[20];

	std::stack<Bitset2D> redo_stack{};
};
