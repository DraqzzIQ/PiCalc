#include "IRenderer.h"

IRenderer::IRenderer()
{
    rendered_pixels = Bitset2D(SCREEN_WIDTH, DynamicBitset(SCREEN_HEIGHT, false));
    rendered_screen_symbols = DynamicBitset(Graphics::SCREEN_SYMBOLS.size(), false);
}

bool IRenderer::already_rendered(const Bitset2D& pixels, const DynamicBitset& screen_symbols)
{
    if(pixels != rendered_pixels || screen_symbols != rendered_screen_symbols)
    {
        rendered_pixels = pixels;
        rendered_screen_symbols = screen_symbols;
        return false;
    }
    return true;
}
