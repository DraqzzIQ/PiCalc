#include "ContrastWindow.h"

ContrastWindow::ContrastWindow()
{
	render();
}

bool ContrastWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == 170) {
		uint8_t contrast = get_contrast();
		if (contrast > 0) set_contrast(contrast - 1);
		render();
		return true;
	} else if (keypress.key_raw == 169) {
		uint8_t contrast = get_contrast();
		if (contrast < 30) set_contrast(contrast + 1);
		render();
		return true;
	} else if (keypress.key_raw == 73) {
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
	_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 12, 54, 53, 59, 57, 40, 58, 59 }, false);
	_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 76, 181, 77, 76, 182, 77 }, false);
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
	uint8_t contrast = 255;
	for (auto renderer : IRenderer::Renderers) {
		contrast = renderer->get_contrast();
		if (contrast != 255) break;
	}
	if (contrast == 255) return 14;
	return contrast;
}

void ContrastWindow::set_contrast(uint8_t contrast)
{
	for (auto renderer : IRenderer::Renderers) {
		renderer->set_contrast(contrast);
	}
}