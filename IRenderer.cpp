#include "IRenderer.h"

IRenderer::IRenderer()
{
    rendered_pixels = bitset_2d(SCREEN_WIDTH, dynamic_bitset(SCREEN_HEIGHT, false));
    rendered_screen_symbols = dynamic_bitset(Graphics::SCREEN_SYMBOLS.size(), false);
}

bool IRenderer::already_rendered(const bitset_2d& pixels, const dynamic_bitset& screen_symbols)
{
    if(pixels != rendered_pixels || screen_symbols != rendered_screen_symbols)
    {
        rendered_pixels = pixels;
        rendered_screen_symbols = screen_symbols;
        return false;
    }
    return true;
}
