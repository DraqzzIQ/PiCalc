#include "keyboard/IKeyboard.h"

IKeyboard::IKeyboard()
{
	_window_manager = WindowManager::get_instance();
}

uint8_t IKeyboard::raw_key_to_calculator_key(uint8_t raw_key, bool shift, bool alpha)
{
	if (shift) {
		if (!Chars::KEY_MAP_SHIFT.contains(raw_key)) return Chars::KEY_MAP_SHIFT.at(Chars::CHAR_TO_KEYCODE.at("unknown"));
		return Chars::KEY_MAP_SHIFT.at(raw_key);
	} else if (alpha) {
		if (!Chars::KEY_MAP_ALPHA.contains(raw_key)) return Chars::KEY_MAP_ALPHA.at(Chars::CHAR_TO_KEYCODE.at("unknown"));
		return Chars::KEY_MAP_ALPHA.at(raw_key);
	} else {
		return raw_key;
	}
}

uint8_t IKeyboard::raw_key_to_keyboard_key(uint8_t raw_key, bool shift, bool alpha)
{
	return 0;
}
