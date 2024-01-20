#include "ContrastWindow.h"

ContrastWindow::ContrastWindow():
	Window()
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
	_window.put_chars(0, 0, Graphics::SYMBOLS_6_HIGH, "Contrast", false);
	_window.put_chars(0, 8, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 76, 181, 77, 76, 182, 77 }, false);
	uint8_t bar_x = (30 - contrast) * 2 + 16;
	for (uint8_t y = 20; y < 28; y++) {
		_window.set_bit(15, y, true);
		_window.set_bit(78, y, true);
		_window.set_bit(bar_x, y, true);
		_window.set_bit(bar_x + 1, y, true);
	}
	for (uint8_t x = 16; x < 78; x++) {
		_window.set_bit(x, 20, true);
		_window.set_bit(x, 27, true);
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