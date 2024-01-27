#include "renderers/IRenderer.h"

std::vector<IRenderer*> IRenderer::Renderers;

IRenderer::IRenderer()
{
	Renderers.push_back(this);
	_rendered_frame = Frame();
}

bool IRenderer::already_rendered(Frame frame)
{
	if (frame.pixels != _rendered_frame.pixels || frame.screen_symbols != _rendered_frame.screen_symbols) {
		_rendered_frame.pixels = frame.pixels;
		_rendered_frame.screen_symbols = frame.screen_symbols;
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