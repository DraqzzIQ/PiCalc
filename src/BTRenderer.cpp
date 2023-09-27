#include "BTRenderer.h"
#ifdef PICO
#include "Constants.h"

BTRenderer::BTRenderer(BTManager* bt_manager)
{
    _bt_manager = bt_manager;
}

void BTRenderer::render(const bitset_2d& pixels, const dynamic_bitset& screen_symbols, bool force_rerender)
{
    if(!force_rerender && already_rendered(pixels, screen_symbols))
        return;

    _bt_manager->send_display_frame(flatten_2d_bitset(pixels).get_bytes(), screen_symbols.get_bytes());
}


dynamic_bitset BTRenderer::flatten_2d_bitset(const bitset_2d& pixels) {
    dynamic_bitset flattened_bitset;
    for (uint32_t i = 0; i < pixels.width(); i++) {
        flattened_bitset.extend(pixels.at(i));
    }
    return flattened_bitset;
}

#endif