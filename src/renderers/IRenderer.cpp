#include "renderers/IRenderer.h"

std::vector<IRenderer*> IRenderer::Renderers;

IRenderer::IRenderer()
{
	Renderers.push_back(this);
	_rendered_frame = Frame(Bitset2D(SCREEN_WIDTH, DynamicBitset(SCREEN_HEIGHT, false)), DynamicBitset(Graphics::SCREEN_SYMBOLS.size(), false));
}

bool IRenderer::already_rendered(const Frame& frame)
{
	if (frame.pixels != _rendered_frame.pixels || frame.screen_symbols != _rendered_frame.screen_symbols) {
		_rendered_frame.pixels = frame.pixels;
		_rendered_frame.screen_symbols = frame.screen_symbols;
		return false;
	}
	return true;
}
