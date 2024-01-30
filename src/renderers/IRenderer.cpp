#include "renderers/IRenderer.h"

std::vector<IRenderer*> IRenderer::Renderers;

IRenderer::IRenderer()
{
	Renderers.push_back(this);
	_rendered_pixels = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

bool IRenderer::already_rendered(const Frame& frame)
{
	if (frame.pixels != _rendered_pixels || frame.screen_symbols != _rendered_screen_symbols || frame.corner_x != _rendered_corner_x || frame.corner_y != _rendered_corner_y) {
		_rendered_pixels = frame.pixels;
		_rendered_screen_symbols = frame.screen_symbols;
		_rendered_corner_x = frame.corner_x;
		_rendered_corner_y = frame.corner_y;
		return false;
	}
	return true;
}

void IRenderer::set_contrast(uint8_t value)
{
}

uint8_t IRenderer::get_contrast()
{
	return 255;
}