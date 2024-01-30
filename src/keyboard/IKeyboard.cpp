#include "keyboard/IKeyboard.h"

IKeyboard::IKeyboard()
{
	_window_manager = WindowManager::get_instance();
}

KEY IKeyboard::raw_key_to_calculator_key(KEY raw_key, bool shift, bool alpha)
{
	if (shift) {
		switch (raw_key) {
		case 7: return 8;
		case 11: return 12;
		case 14: return 33;
		case 16: return 17;
		case 18: return 19;
		case 20: return 21;
		case 22: return 23;
		case 24: return 25;
		case 26: return 27;
		case 29: return 30;
		case 129: return 132;
		case 130: return 133;
		case 131: return 134;
		case 141: return 142;
		case 143: return 144;
		case 40: return 37;
		case 41: return 59;
		case 145: return 146;
		case 147: return 148;
		case 55: return 149;
		case 56: return 150;
		case 57: return 152;
		case 153: return 154;
		case 155: return 156;
		case 54: return 157;
		case 215: return 158;
		case 247: return 160;
		case 49: return 162;
		case 51: return 163;
		case 43: return 164;
		case 45: return 166;
		case 48: return 168;
		case 44: return 169;
		case 171: return 172;
		case 178: return 179;
		case 73: return 180;
		default: return 0;
		}
	} else if (alpha) {
		switch (raw_key) {
		case 13: return 58;
		case 28: return 65;
		case 29: return 66;
		case 31: return 67;
		case 129: return 68;
		case 130: return 69;
		case 131: return 70;
		case 41: return 88;
		case 145: return 89;
		case 147: return 77;
		case 56: return 151;
		case 215: return 159;
		case 247: return 161;
		case 43: return 165;
		case 45: return 167;
		case 44: return 170;
		case 171: return 173;
		default: return 0;
		}
	} else {
		return raw_key;
	}
}