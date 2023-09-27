#pragma once
#ifdef PICO
#include "IRenderer.h"
#include "WindowManager.h"
#include "BTManager.h"


class BTRenderer : public IRenderer
{
    public:
        BTRenderer(BTManager* bt_manager);
        void render(render_plane pixels, std::vector<bool> screen_symbols, bool force_rerender);
    private:
        BTManager* _bt_manager;
        std::vector<bool> flatten_2d_bool_vector(const std::vector<std::vector<bool>>& bool_matrix);
        std::vector<uint8_t> convert_bools_to_bits(const std::vector<bool>& bools);
};

#endif