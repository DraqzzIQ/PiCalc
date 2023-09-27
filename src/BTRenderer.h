#pragma once
#ifdef PICO
#include "IRenderer.h"
#include "WindowManager.h"
#include "BTManager.h"


class BTRenderer : public IRenderer
{
    public:
        BTRenderer(BTManager* bt_manager);
        void render(const bitset_2d& pixels, const dynamic_bitset& screen_symbols, bool force_rerender);
    private:
        BTManager* _bt_manager;
        dynamic_bitset flatten_2d_bitset(const bitset_2d& bool_matrix);
};

#endif