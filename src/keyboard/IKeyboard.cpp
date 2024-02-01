#include "keyboard/IKeyboard.h"

IKeyboard::IKeyboard()
{
	_window_manager = WindowManager::get_instance();
}

KEY IKeyboard::raw_key_to_calculator_key(KEY raw_key, bool shift, bool alpha)
{
	if (shift) {
		switch (raw_key) {
		case KEY_SETUP: return KEY_MODE;
		case KEY_ABS: return KEY_MOD;
		case KEY_RECIPROCAL: return '!';
		case KEY_FRACTION: return KEY_MIXED_FRACTION;
		case KEY_SQRT: return KEY_ROOT3;
		case KEY_SQUARED: return KEY_PERIODIC;
		case KEY_POWER: return KEY_ROOTN;
		case KEY_LOG: return KEY_POWER10;
		case KEY_LN: return KEY_EXP;
		case KEY_TIME: return KEY_FACT;
		case KEY_SIN: return KEY_ASIN;
		case KEY_COS: return KEY_ACOS;
		case KEY_TAN: return KEY_ATAN;
		case KEY_RCL: return KEY_STO;
		case KEY_ENG: return KEY_BACK_ENG;
		case '(': return '%';
		case ')': return ';';
		case KEY_S_D: return KEY_MF_F;
		case KEY_M_PLUS: return KEY_M_MINUS;
		case '7': return KEY_CONST;
		case '8': return KEY_SHIFT_CONV;
		case '9': return KEY_CLR;
		case KEY_DEL: return KEY_INS;
		case KEY_AC: return KEY_OFF;
		case '6': return KEY_VERIFY;
		case KEY_MULTIPLY: return KEY_NPR;
		case KEY_DIVIDE: return KEY_NCR;
		case '1': return KEY_STAT_DIST;
		case '3': return KEY_BASE;
		case '+': return KEY_POL;
		case '-': return KEY_REC;
		case '0': return KEY_RND;
		case ',': return KEY_RAN;
		case KEY_SCIENTIFIC_E: return KEY_PI;
		case KEY_ANS: return KEY_DRG;
		case '=': return KEY_WAVY_EQUAL;
		default: return 0;
		}
	} else if (alpha) {
		switch (raw_key) {
		case KEY_CUBED: return ':';
		case KEY_NEGATE: return 'A';
		case KEY_TIME: return 'B';
		case KEY_HYP: return 'C';
		case KEY_SIN: return 'D';
		case KEY_COS: return 'E';
		case KEY_TAN: return 'F';
		case ')': return 'X';
		case KEY_S_D: return 'Y';
		case KEY_M_PLUS: return 'M';
		case '8': return KEY_ALPHA_CONV;
		case KEY_MULTIPLY: return KEY_GCD;
		case KEY_DIVIDE: return KEY_LCM;
		case '+': return KEY_INT;
		case '-': return KEY_INTG;
		case ',': return KEY_RAN_INT;
		case KEY_SCIENTIFIC_E: return KEY_EULER;
		default: return 0;
		}
	} else {
		return raw_key;
	}
}