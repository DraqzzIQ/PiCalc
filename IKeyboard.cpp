#include "IKeyboard.h"

IKeyboard::IKeyboard(WindowManager *window_manager)
{
    _window_manager = window_manager;
}

uint8_t IKeyboard::raw_key_to_calculator_key(uint8_t raw_key, bool shift, bool alpha)
{
    if (shift) {
        return Chars::KEY_MAP_SHIFT.at(raw_key);
    }
    else if (alpha) {
        return Chars::KEY_MAP_ALPHA.at(raw_key);
    }
    else {
        return raw_key;
    }
}

uint8_t IKeyboard::raw_key_to_keyboard_key(uint8_t raw_key, bool shift, bool alpha)
{
    return 0;
}