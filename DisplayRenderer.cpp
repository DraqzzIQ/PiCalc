#include "DisplayRenderer.h"
#ifdef PICO

DisplayRenderer::DisplayRenderer()
{
    Utils::sleep_for_ms(1);
    init_i2c();
    clear();
}

void DisplayRenderer::render(render_plane pixels, const std::vector<bool> screen_symbols)
{
    if(check_rendered(pixels, screen_symbols))
        return;

    //DONT FORGET::: only 3 commands when sub device addressess are properly implemented
    //3  * 3 commands + 4 bytes per column
    uint8_t command[3 * 3 + 4 * SCREEN_WIDTH] = {select_device(A_SUB_ADDRESS_0, true), load_x_address(COLUMN_ZERO_ADDRESS, true), ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, false)};

    uint8_t index = 3;

    for(size_t j  = 0; j < SCREEN_WIDTH; j++)
    {
        //make 32 heigh so it's eavenly divided by 8
        pixels[j].push_back(false);
        for(size_t i = SCREEN_HEIGHT + 1; i > 0; i-=8)
        {
            uint8_t byte = 0;
            for(size_t k = 0; k < 8; k++)
            {
                if(pixels[j][i - k - 1])
                    byte |= 1 << k;
            }
            command[index++] = byte;

            //hopefully only temporary until sub device addressess are properly implemented
            if(j == 39)
            {
                command[index++] = select_device(A_SUB_ADDRESS_1, true);
                command[index++] = load_x_address(COLUMN_ZERO_ADDRESS, true);
                command[index++] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, false);
            }
            if(j == 79)
            {
                command[index++] = select_device(A_SUB_ADDRESS_2, true);
                command[index++] = load_x_address(COLUMN_ZERO_ADDRESS, true);
                command[index++] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, false);
            }
        }
    }

    i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), false);
}


void DisplayRenderer::init_i2c()
{
    i2c_init(i2c_default, 100000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

void DisplayRenderer::clear()
{
    for (size_t sub_address : sub_devices) {
        uint8_t command[2] = {select_device(sub_address, true), set_mode(T_ROW_MODE, E_BLANK_STATUS, M_1_32_MULTIPLEX, false) };
        i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), false);
    }
}

uint8_t DisplayRenderer::set_mode(uint8_t mode, uint8_t status, uint8_t mux_mode, bool command_following = false)
{
    return command_following + SET_MODE + mode + status + mux_mode;
}
uint8_t DisplayRenderer::select_device(uint8_t addr, bool command_following = false)
{
    return command_following + DEVICE_SELECT + addr;
}
uint8_t DisplayRenderer::ram_access(uint8_t access_mode, uint8_t row_address, bool command_following = false)
{
    return command_following + RAM_ACCESS + access_mode + row_address;
}
uint8_t DisplayRenderer::load_x_address(uint8_t column_address, bool command_following = false)
{
    return command_following + LOAD_X_ADDRESS + column_address;
}
#endif