#include "windows/PaintWindow.h"

PaintWindow::PaintWindow()
{
    _rendered = Bitset2D(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, false);
	_cursor[0] = Constants::SCREEN_WIDTH / 2;
	_cursor[1] = Constants::SCREEN_HEIGHT / 2;
}

PaintWindow::~PaintWindow() {}

Bitset2D PaintWindow::update_window()
{
	return _rendered;
}

void PaintWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_calculator == Chars::KEY_MAP.at('down')) {
        _cursor[1]--;
        if (_cursor[1] < 0) _cursor[1] = 0;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at('up')) {
        _cursor[1]++;
        if (_cursor[1] >= Constants::SCREEN_HEIGHT) _cursor[1] = Constants::SCREEN_HEIGHT - 1;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at('left')) {
        _cursor[0]--;
        if (_cursor[0] < 0) _cursor[0] = 0;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at('right')) {
        _cursor[0]++;
        if (_cursor[0] >= Constants::SCREEN_WIDTH) _cursor[0] = Constants::SCREEN_WIDTH - 1;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at('=')) {
        _pen_down = !_pen_down;
    }
    else if (keypress.key_calculator == Chars::KEY_MAP.at('AC')) {
        _rendered = Bitset2D(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, false);
    }
	// if (_pen_down) _rendered.set(_cursor[0], _cursor[1], true);
}