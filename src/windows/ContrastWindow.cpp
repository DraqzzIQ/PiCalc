#include "windows/ContrastWindow.h"

ContrastWindow::ContrastWindow()
{
	render();
}

bool ContrastWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == KEY_RIGHT) {
		uint8_t contrast = get_contrast();
		if (contrast > 0) set_contrast(contrast - 1);
		render();
		return true;
	} else if (keypress.key_raw == KEY_LEFT) {
		uint8_t contrast = get_contrast();
		if (contrast < 30) set_contrast(contrast + 1);
		render();
		return true;
	} else if (keypress.key_raw == '=') {
		set_contrast(14);
		render();
		return true;
	}
	return false;
}

void ContrastWindow::render()
{
	uint8_t contrast = get_contrast();
	clear_window();
	_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Contrast:", false);
	_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 91, 186, 93, 91, 187, 93 }, false);
	uint8_t bar_x = (30 - contrast) * 2 + 16;
	_window.draw_vertical_line(15, 21, 8, true);
	_window.draw_vertical_line(78, 21, 8, true);
	_window.draw_vertical_line(bar_x, 21, 8, true);
	_window.draw_vertical_line(bar_x + 1, 21, 8, true);
	for (uint8_t x = 16; x < 78; x++) {
		_window.set_bit(x, 21, true);
		_window.set_bit(x, 28, true);
	}
}

uint8_t ContrastWindow::get_contrast()
{
#ifdef PICO
	return I2CUtils::get_contrast();
#endif
	return 14;
}

void ContrastWindow::set_contrast(uint8_t contrast)
{
#ifdef PICO
	I2CUtils::set_contrast(contrast);
#endif
}