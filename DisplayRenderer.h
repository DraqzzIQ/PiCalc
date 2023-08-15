#pragma once
#ifdef PICO
#include "IRenderer.h"
#include "LCDConstants.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <cmath>

/// <summary>
/// provides functionality to render to the display
/// </summary>
class DisplayRenderer : public IRenderer
{
    public:
        DisplayRenderer();

        /// <summary>
        /// renders the given pixels to the console
        /// </summary>
        /// <param name="pixels">pixels to render</param>
        void render(render_plane pixels, std::vector<bool> screen_symbols);
    private:
        /// <summary>
        /// clears the display
        /// </summary>
        void clear();
        /// <summary>
        /// initializes the i2c connection
        /// </summary>
        void init_i2c();
        /// <summary>
        /// sub_addresses for the display chips
        /// </summary>
        uint8_t sub_devices[3] = {A_SUB_ADDRESS_0, A_SUB_ADDRESS_1, A_SUB_ADDRESS_2};
        /// <summary>
        /// sets the mode of the display
        /// </summary>
        uint8_t set_mode(uint8_t mode, uint8_t status, uint8_t mux_mode, bool command_following);
        /// <summary>
        /// selects the device at the given address
        /// </summary>
        uint8_t select_device(uint8_t addr, bool command_following);
        /// <summary>
        /// accesses the ram at the given address
        /// </summary>
        uint8_t ram_access(uint8_t access_mode, uint8_t row_address, bool command_following);
        /// <summary>
        /// loads the x (column) address
        /// </summary>
        uint8_t load_x_address(uint8_t column_address, bool command_following );
};
#endif