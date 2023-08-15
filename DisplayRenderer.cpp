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
    uint8_t command[163];
    command[0] = select_device(A_SUB_ADDRESS_0, C_COMMAND_FOLLOWING);
    command[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
    command[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

    uint16_t index = 3;
    printf("Hallo2\n");

    for(size_t j  = 0; j < 40; j++)
    {
        //make 32 heigh so it's eavenly divided by 8
        pixels[j].push_back(false);
        for(size_t i = 0; i < SCREEN_HEIGHT + 1; i+=8)
        {
            uint8_t byte = 0;
            for(size_t k = 0; k < 8; k++)
            {
                if(pixels[j][i + k])
                    byte |= 1 << k;
            }
            command[index++] = byte;
        }
    }
    i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);

    command[0] = select_device(A_SUB_ADDRESS_1, C_COMMAND_FOLLOWING);
    command[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
    command[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

    index = 3;
    
    for(size_t j  = 40; j < 80; j++)
    {
        //make 32 heigh so it's eavenly divided by 8
        pixels[j].push_back(false);
        for(size_t i = 0; i < SCREEN_HEIGHT + 1; i+=8)
        {
            uint8_t byte = 0;
            for(size_t k = 0; k < 8; k++)
            {
                if(pixels[j][i + k])
                    byte |= 1 << k;
            }
            command[index++] = byte;
        }
    }

    i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), C_LAST_COMMAND);

    uint8_t command2[67];
    command2[0] = select_device(A_SUB_ADDRESS_2, C_COMMAND_FOLLOWING);
    command2[1] = load_x_address(COLUMN_ZERO_ADDRESS, C_COMMAND_FOLLOWING);
    command2[2] = ram_access(G_RAM_FULL_GRAPHIC_MODE, BANK_ZERO_ADDRESS, C_LAST_COMMAND);

    index = 3;
    
    for(size_t j  = 80; j < 96; j++)
    {
        //make 32 heigh so it's eavenly divided by 8
        pixels[j].push_back(false);
        for(size_t i = 0; i < SCREEN_HEIGHT + 1; i+=8)
        {
            uint8_t byte = 0;
            for(size_t k = 0; k < 8; k++)
            {
                if(pixels[j][i + k])
                    byte |= 1 << k;
            }
            command2[index++] = byte;
        }
    }
    i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command2, sizeof(command2), C_LAST_COMMAND);
}


void DisplayRenderer::init_i2c()
{
    i2c_init(i2c_default, 100000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
}

void DisplayRenderer::clear()
{
    uint8_t command[1] = { set_mode(T_ROW_MODE, E_NORMAL_STATUS, M_1_32_MULTIPLEX, false) };
    i2c_write_blocking(i2c_default, DEVICE_ADDRESS, command, sizeof(command), false);
}

uint8_t DisplayRenderer::set_mode(uint8_t mode, uint8_t status, uint8_t mux_mode, uint8_t command_following)
{
    return command_following + SET_MODE + mode + status + mux_mode;
}
uint8_t DisplayRenderer::select_device(uint8_t addr, uint8_t command_following)
{
    printf("device select: %d\n", command_following + DEVICE_SELECT + addr);
    return command_following + DEVICE_SELECT + addr;
}
uint8_t DisplayRenderer::ram_access(uint8_t access_mode, uint8_t row_address, uint8_t command_following)
{
    return command_following + RAM_ACCESS + access_mode + row_address;
}
uint8_t DisplayRenderer::load_x_address(uint8_t column_address, uint8_t command_following)
{
    return command_following + LOAD_X_ADDRESS + column_address;
}
#endif