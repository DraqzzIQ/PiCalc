#include "IRenderer.h"

IRenderer::IRenderer()
{
    rendered_pixels =  render_plane(SCREEN_WIDTH, std::vector<bool>(SCREEN_HEIGHT + 1, false));
    rendered_screen_symbols = std::vector<bool>(Graphics::SCREEN_SYMBOLS.size(), false);
}

bool IRenderer::check_rendered(const render_plane pixels, const std::vector<bool> screen_symbols)
{
    if (pixels.size() != rendered_pixels.size() || screen_symbols.size() != rendered_screen_symbols.size())
    {
        rendered_pixels = pixels;
        rendered_screen_symbols = screen_symbols;
        return false;
    }

    for (size_t i = 0; i < pixels.size(); i++)
    {
        if (pixels[i] != rendered_pixels[i])
        {
            rendered_pixels = pixels;
            rendered_screen_symbols = screen_symbols;
            return false;
        }
    }
    for (int i = 0; i < screen_symbols.size(); i++)
    {
        if (screen_symbols[i] != rendered_screen_symbols[i])
        {
            rendered_pixels = pixels;
            rendered_screen_symbols = screen_symbols;
            return false;
        }
    }
    return true;
}
