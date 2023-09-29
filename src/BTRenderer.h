#pragma once
#ifdef PICO
#include "IRenderer.h"
#include "WindowManager.h"
#include "BTManager.h"


class BTRenderer : public IRenderer
{
    public:
        BTRenderer(BTManager* bt_manager);
        void render(const Bitset2D& pixels, const DynamicBitset& screen_symbols, bool force_rerender);
    private:
        BTManager* _bt_manager;
        DynamicBitset flatten_2d_bitset(const Bitset2D& bool_matrix);
};

#endif