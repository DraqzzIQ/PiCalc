#pragma once
#ifdef PICO
#include "IRenderer.h"
#include "LCDConstants.h"
#include "hardware/i2c.h"

class DisplayRenderer : public IRenderer
{
    public:
        DisplayRenderer();

        /// <summary>
        /// renders the given pixels to the console
        /// </summary>
        /// <param name="pixels">pixels to render</param>
        void render(const render_plane pixels, std::vector<bool> screen_symbols);
};
#endif