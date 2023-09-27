#include "BTRenderer.h"
#ifdef PICO
#include "Constants.h"

BTRenderer::BTRenderer(BTManager* bt_manager)
{
    _bt_manager = bt_manager;
}

void BTRenderer::render(render_plane pixels, std::vector<bool> screen_symbols, bool force_rerender)
{
    if(!force_rerender && already_rendered(pixels, screen_symbols))
        return;

    _bt_manager->send_display_frame(convert_bools_to_bits(flatten_2d_bool_vector(pixels)), convert_bools_to_bits(screen_symbols));
}


std::vector<bool> BTRenderer::flatten_2d_bool_vector(const std::vector<std::vector<bool>>& bool_matrix) {
    std::vector<bool> flattened_vector;
    for (const std::vector<bool>& column : bool_matrix) {
        flattened_vector.insert(flattened_vector.end(), column.begin(), column.end());
    }
    return flattened_vector;
}

std::vector<uint8_t> BTRenderer::convert_bools_to_bits(const std::vector<bool>& bools) {
    std::vector<uint8_t> bits;
    for (size_t i = 0; i < bools.size(); i += 8) {
        uint8_t byte = 0;
        for (size_t j = 0; j < 8; ++j) {
            if (i + j < bools.size()) {
                byte |= (bools[i + j] << j);
            }
        }
        bits.push_back(byte);
    }
    return bits;
}

#endif