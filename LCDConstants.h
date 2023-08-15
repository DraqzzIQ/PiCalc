#define SET_MODE 0b01000000
#define SET_START_BANK 0b01111100
#define DEVICE_SELECT 0b01100000
#define RAM_ACCESS 0b01110000
#define LOAD_X_ADDRESS 0b00000000

#define C_LAST_COMMAND 0b00000000
#define C_COMMAND_FOLLOWING 0b10000000

#define T_ROW_MODE 0b00000000
#define T_MIXED_MODE 0b0001000

#define E_BLANK_STATUS 0b00000000
#define E_NORMAL_STATUS 0b00000100
#define E_ALL_ON_STATUS 0b00001000
#define E_INVERSE_STATUS 0b00001100

#define M_1_32_MULTIPLEX 0b00000000

#define B_SET_START_BANK_0 0b00000000
#define B_SET_START_BANK_1 0b00000001
#define B_SET_START_BANK_2 0b00000010
#define B_SET_START_BANK_3 0b00000011

#define G_RAM_CHARACTER_MODE 0b00000000
#define G_RAM_HALF_GRAPHIC_MODE 0b00000100
#define G_RAM_FULL_GRAPHIC_MODE 0b00001000
#define G_RAM_NOT_ALLOWED_MODE 0b00001100

#define A_MASTER_ADDRESS 0b00000000 //master 

#define A_SUB_ADDRESS_0 0b00000011 //Column 0-39
#define A_SUB_ADDRESS_1 0b00000001 // Column 40-79
#define A_SUB_ADDRESS_2 0b00000010 // Column 80-95

#define DEVICE_ADDRESS 0b00111100

#define COLUMN_ZERO_ADDRESS 0b00000000

#define BANK_ZERO_ADDRESS 0b00000000