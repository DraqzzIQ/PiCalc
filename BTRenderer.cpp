#include "BTRenderer.h"
#ifdef PICO
#include "Constants.h"

BTRenderer::BTRenderer(BTManager* bt_manager)
{
    _bt_manager = bt_manager;
}

void BTRenderer::render(const render_plane& pixels, const dynamic_bitset& screen_symbols, bool force_rerender)
{
    if(!force_rerender && already_rendered(pixels, screen_symbols))
        return;

    _bt_manager->send_display_frame(flatten_2d_bitset(pixels).get_bytes(), screen_symbols.get_bytes());
}


dynamic_bitset BTRenderer::flatten_2d_bitset(const render_plane& bitset_2d) {
    dynamic_bitset flattened_bitset;
    for (const dynamic_bitset& column : bitset_2d) {
        flattened_bitset.append(column);
    }
    return flattened_bitset;
}

#endif