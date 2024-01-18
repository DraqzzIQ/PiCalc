#include "keyboard/IKeyboard.h"

IKeyboard::IKeyboard()
{
	_window_manager = WindowManager::get_instance();
}

KEY IKeyboard::raw_key_to_calculator_key(KEY raw_key, bool shift, bool alpha)
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

KEY IKeyboard::raw_key_to_keyboard_key(KEY raw_key, bool shift, bool alpha)
{
	if (shift) {
		if (raw_key < 10) return raw_key;
		switch (raw_key) {
		case 106: return Chars::CHAR_TO_KEYCODE.at("A");
		case 107: return Chars::CHAR_TO_KEYCODE.at("B");
		case 108: return Chars::CHAR_TO_KEYCODE.at("C");
		case 109: return Chars::CHAR_TO_KEYCODE.at("D");
		case 110: return Chars::CHAR_TO_KEYCODE.at("E");
		case 111: return Chars::CHAR_TO_KEYCODE.at("F");
		case 112: return Chars::CHAR_TO_KEYCODE.at("G");
		case 113: return Chars::CHAR_TO_KEYCODE.at("H");
		case 114: return Chars::CHAR_TO_KEYCODE.at("I");
		case 115: return Chars::CHAR_TO_KEYCODE.at("J");
		case 116: return Chars::CHAR_TO_KEYCODE.at("K");
		case 102: return Chars::CHAR_TO_KEYCODE.at("L");
		case 117: return Chars::CHAR_TO_KEYCODE.at("M");
		case 118: return Chars::CHAR_TO_KEYCODE.at("N");
		case 119: return Chars::CHAR_TO_KEYCODE.at("O");
		case 120: return Chars::CHAR_TO_KEYCODE.at("P");
		case 121: return Chars::CHAR_TO_KEYCODE.at("Q");
		case 122: return Chars::CHAR_TO_KEYCODE.at("R");
		case 74: return Chars::CHAR_TO_KEYCODE.at("S");
		case 75: return Chars::CHAR_TO_KEYCODE.at("T");
		case 123: return Chars::CHAR_TO_KEYCODE.at("U");
		case 124: return Chars::CHAR_TO_KEYCODE.at("V");
		case 71: return Chars::CHAR_TO_KEYCODE.at("W");
		case 72: return Chars::CHAR_TO_KEYCODE.at("X");
		case 69: return Chars::CHAR_TO_KEYCODE.at("Y");
		case 70: return Chars::CHAR_TO_KEYCODE.at("Z");
		case 82: return Chars::CHAR_TO_KEYCODE.at(";");
		case 127: return Chars::CHAR_TO_KEYCODE.at("!");
		case 128: return Chars::CHAR_TO_KEYCODE.at("?");
		}
	} else {
		if (raw_key < 10) return raw_key;
		switch (raw_key) {
		case 106: return Chars::CHAR_TO_KEYCODE.at("a");
		case 107: return Chars::CHAR_TO_KEYCODE.at("b");
		case 108: return Chars::CHAR_TO_KEYCODE.at("c");
		case 109: return Chars::CHAR_TO_KEYCODE.at("d");
		case 110: return Chars::CHAR_TO_KEYCODE.at("e");
		case 111: return Chars::CHAR_TO_KEYCODE.at("f");
		case 112: return Chars::CHAR_TO_KEYCODE.at("g");
		case 113: return Chars::CHAR_TO_KEYCODE.at("h");
		case 114: return Chars::CHAR_TO_KEYCODE.at("i");
		case 115: return Chars::CHAR_TO_KEYCODE.at("j");
		case 116: return Chars::CHAR_TO_KEYCODE.at("k");
		case 102: return Chars::CHAR_TO_KEYCODE.at("l");
		case 117: return Chars::CHAR_TO_KEYCODE.at("m");
		case 118: return Chars::CHAR_TO_KEYCODE.at("n");
		case 119: return Chars::CHAR_TO_KEYCODE.at("o");
		case 120: return Chars::CHAR_TO_KEYCODE.at("p");
		case 121: return Chars::CHAR_TO_KEYCODE.at("q");
		case 122: return Chars::CHAR_TO_KEYCODE.at("r");
		case 74: return Chars::CHAR_TO_KEYCODE.at("s");
		case 75: return Chars::CHAR_TO_KEYCODE.at("t");
		case 123: return Chars::CHAR_TO_KEYCODE.at("u");
		case 124: return Chars::CHAR_TO_KEYCODE.at("v");
		case 71: return Chars::CHAR_TO_KEYCODE.at("w");
		case 72: return Chars::CHAR_TO_KEYCODE.at("x");
		case 69: return Chars::CHAR_TO_KEYCODE.at("y");
		case 70: return Chars::CHAR_TO_KEYCODE.at("z");
		case 82: return Chars::CHAR_TO_KEYCODE.at(",");
		case 127: return Chars::CHAR_TO_KEYCODE.at(".");
		case 128: return Chars::CHAR_TO_KEYCODE.at(" ");
		}
	}
	return Chars::CHAR_TO_KEYCODE.at("unknown");
}