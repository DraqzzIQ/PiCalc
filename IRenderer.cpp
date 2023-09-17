#include "IRenderer.h"

IRenderer::IRenderer()
{
    rendered_pixels = render_plane(SCREEN_WIDTH, dynamic_bitset(SCREEN_HEIGHT, false));
    rendered_screen_symbols = dynamic_bitset(Graphics::SCREEN_SYMBOLS.size(), false);
}

bool IRenderer::already_rendered(const render_plane& pixels, const dynamic_bitset& screen_symbols)
{
    if(pixels != rendered_pixels || screen_symbols != rendered_screen_symbols)
    {
        rendered_pixels = pixels;
        rendered_screen_symbols = screen_symbols;
        return false;
    }
    return true;
}
