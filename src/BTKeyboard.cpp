#include "BTKeyboard.h"
#ifdef PICO

BTKeyboard::BTKeyboard(WindowManager* window_manager): IKeyboard(window_manager) {}

void BTKeyboard::handle_keyboard_press(uint8_t bt_keycode)
{
	_window_manager->handle_key_down(get_key_press(bt_keycode));
}

KeyPress BTKeyboard::get_key_press(uint8_t bt_keycode)
{
	KeyPress key_press;
	key_press.shift = is_shift_active();
	key_press.alpha = is_alpha_active();
	key_press.key_raw = bt_keycode_to_raw_key(bt_keycode);
	key_press.key_calculator = raw_key_to_calculator_key(key_press.key_raw, key_press.shift, key_press.alpha);
	key_press.key_keyboard = raw_key_to_keyboard_key(key_press.key_raw, key_press.shift, key_press.alpha);

	if (key_press.key_raw == Chars::KEY_MAP.at("SHIFT")) functionKeysState = FunctionKeyState::SHIFT_ON;
	else if (key_press.key_raw == Chars::KEY_MAP.at("ALPHA")) functionKeysState = FunctionKeyState::ALPHA_ON;
	else functionKeysState = FunctionKeyState::OFF;

	return key_press;
}

uint8_t BTKeyboard::bt_keycode_to_raw_key(uint8_t bt_keycode)
{
	switch (bt_keycode) {
	case 0: return Chars::KEY_MAP.at("0");
	case 1: return Chars::KEY_MAP.at(",");
	case 2: return Chars::KEY_MAP.at("*10^n");
	case 3: return Chars::KEY_MAP.at("Ans");
	case 4: return Chars::KEY_MAP.at("=");
	case 5: return Chars::KEY_MAP.at("1");
	case 6: return Chars::KEY_MAP.at("2");
	case 7: return Chars::KEY_MAP.at("3");
	case 8: return Chars::KEY_MAP.at("+");
	case 9: return Chars::KEY_MAP.at("-");
	case 10: return Chars::KEY_MAP.at("4");
	case 11: return Chars::KEY_MAP.at("5");
	case 12: return Chars::KEY_MAP.at("6");
	case 13: return Chars::KEY_MAP.at("multiply");
	case 14: return Chars::KEY_MAP.at("divide");
	case 15: return Chars::KEY_MAP.at("7");
	case 16: return Chars::KEY_MAP.at("8");
	case 17: return Chars::KEY_MAP.at("9");
	case 18: return Chars::KEY_MAP.at("DEL");
	case 19: return Chars::KEY_MAP.at("AC");
	case 20: return Chars::KEY_MAP.at("RCL");
	case 21: return Chars::KEY_MAP.at("ENG");
	case 22: return Chars::KEY_MAP.at("(");
	case 23: return Chars::KEY_MAP.at(")");
	case 24: return Chars::KEY_MAP.at("S<>D");
	case 25: return Chars::KEY_MAP.at("M+");
	case 26: return Chars::KEY_MAP.at("(-)");
	case 27: return Chars::KEY_MAP.at("time");
	case 28: return Chars::KEY_MAP.at("hyp");
	case 29: return Chars::KEY_MAP.at("sin");
	case 30: return Chars::KEY_MAP.at("cos");
	case 31: return Chars::KEY_MAP.at("tan");
	case 32: return Chars::KEY_MAP.at("fraction");
	case 33: return Chars::KEY_MAP.at("root2");
	case 34: return Chars::KEY_MAP.at("x^2");
	case 35: return Chars::KEY_MAP.at("x^n");
	case 36: return Chars::KEY_MAP.at("log10");
	case 37: return Chars::KEY_MAP.at("ln");
	case 38: return Chars::KEY_MAP.at("Abs");
	case 39: return Chars::KEY_MAP.at("x^3");
	case 40: return Chars::KEY_MAP.at("x^-1");
	case 41: return Chars::KEY_MAP.at("logn");
	case 42: return Chars::KEY_MAP.at("left");
	case 43: return Chars::KEY_MAP.at("right");
	case 44: return Chars::KEY_MAP.at("up");
	case 45: return Chars::KEY_MAP.at("down");
	case 46: return Chars::KEY_MAP.at("SHIFT");
	case 47: return Chars::KEY_MAP.at("ALPHA");
	case 48: return Chars::KEY_MAP.at("MODE");
	case 49: return Chars::KEY_MAP.at("ON");
	default: return Chars::KEY_MAP.at("unknown");
	}
}

bool BTKeyboard::is_shift_active()
{
	return functionKeysState == FunctionKeyState::SHIFT_ON;
}

bool BTKeyboard::is_alpha_active()
{
	return functionKeysState == FunctionKeyState::ALPHA_ON;
}

void BTKeyboard::check_for_keyboard_presses()
{
	// Unused
}

#endif