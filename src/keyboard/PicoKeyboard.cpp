#ifdef PICO
#include "Keyboard.h"

Keyboard::KeyState Keyboard::_function_keys_state = Keyboard::KeyState::ON;
const std::vector<uint8_t> Keyboard::_inputs{ 2, 3, 6, 7, 8, 9, 10, 11, 12 };
const std::vector<uint8_t> Keyboard::_outputs{ 13, 14, 15, 20, 21, 22 };
std::vector<std::vector<Keyboard::KeyState>> Keyboard::_pressed_buttons = std::vector<std::vector<KeyState>>(_outputs.size(), std::vector<Keyboard::KeyState>(_inputs.size(), Keyboard::KeyState::OFF));

void Keyboard::init()
{
	stdio_init_all();

	for (auto& pin : _outputs) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);
	}

	for (auto& pin : _inputs) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_down(pin);
	}
}

bool Keyboard::is_shift_active()
{
	return _function_keys_state == KeyState::SHIFT_ON;
}

bool Keyboard::is_alpha_active()
{
	return _function_keys_state == KeyState::ALPHA_ON;
}

void Keyboard::check_for_keyboard_presses()
{
	for (uint8_t px = 0; px < _outputs.size(); px++) {
		set_pin(px);
		sleep_ms(10);
		std::vector<bool> high_pins = get_pins();
		for (uint8_t py = 0; py < high_pins.size(); py++) {
			if (_pressed_buttons[px][py] == KeyState::OFF && high_pins[py]) {
				KeyPress press = coords_to_keypress(px, py, _function_keys_state);
				// std::cout << "\nKey pressed: " << unsigned(press.key_calculator) << std::endl; // uncomment to test keys via picoprobe / serial output
				WindowManager::handle_key_down(press); // comment to test keys via picoprobe / serial output
				_pressed_buttons[px][py] = _function_keys_state;

				if (press.key_raw == KEY_SHIFT) _function_keys_state = KeyState::SHIFT_ON;
				else if (press.key_raw == KEY_ALPHA) _function_keys_state = KeyState::ALPHA_ON;
				else _function_keys_state = KeyState::ON;
			} else if (_pressed_buttons[px][py] != KeyState::OFF && !high_pins[py]) {
				KeyPress release = coords_to_keypress(px, py, _pressed_buttons[px][py]);
				// std::cout << "\nKey released: " << unsigned(release.key_calculator) << std::endl; // uncomment to test keys via picoprobe / serial output
				WindowManager::handle_key_up(release); // comment to test keys via picoprobe / serial output
				_pressed_buttons[px][py] = KeyState::OFF;
			}
		}
	}
}

KEY Keyboard::coords_to_key_raw(uint8_t x, uint8_t y)
{
	switch (10 * x + y) {
	case 0: return KEY_SHIFT;
	case 1: return KEY_ABS;
	case 2: return KEY_FRACTION;
	case 3: return KEY_NEGATE;
	case 4: return KEY_RCL;
	case 5: return '7';
	case 6: return '4';
	case 7: return '1';
	case 8: return '0';
	case 10: return KEY_ALPHA;
	case 11: return KEY_CUBED;
	case 12: return KEY_SQRT;
	case 13: return KEY_TIME;
	case 14: return KEY_ENG;
	case 15: return '8';
	case 16: return '5';
	case 17: return '2';
	case 18: return ',';
	case 20: return KEY_LEFT;
	case 21: return KEY_DOWN;
	case 22: return KEY_SQUARED;
	case 23: return KEY_HYP;
	case 24: return '(';
	case 25: return '9';
	case 26: return '6';
	case 27: return '3';
	case 28: return KEY_SCIENTIFIC_E;
	case 30: return KEY_UP;
	case 31: return KEY_RECIPROCAL;
	case 32: return KEY_POWER;
	case 33: return KEY_SIN;
	case 34: return ')';
	case 35: return KEY_DEL;
	case 36: return KEY_MULTIPLY;
	case 37: return '+';
	case 38: return KEY_ANS;
	case 40: return KEY_RIGHT;
	case 41: return KEY_LOGN;
	case 42: return KEY_LOG;
	case 43: return KEY_COS;
	case 44: return KEY_S_D;
	case 45: return KEY_AC;
	case 46: return KEY_DIVIDE;
	case 47: return '-';
	case 48: return '=';
	case 50: return KEY_MODE;
	case 52: return KEY_LN;
	case 53: return KEY_TAN;
	case 54: return KEY_M_PLUS;
	default: return 0;
	}
}

KEY Keyboard::raw_key_to_keyboard_key(KEY raw_key, bool shift, bool alpha)
{
	if (shift) {
		if (raw_key > 47 && raw_key < 58) return raw_key;
		switch (raw_key) {
		case 11: return 'A';
		case 13: return 'B';
		case 14: return 'C';
		case 15: return 'D';
		case 16: return 'E';
		case 18: return 'F';
		case 20: return 'G';
		case 22: return 'H';
		case 24: return 'I';
		case 26: return 'J';
		case 28: return 'K';
		case 29: return 'L';
		case 31: return 'M';
		case 129: return 'N';
		case 130: return 'O';
		case 131: return 'P';
		case 141: return 'Q';
		case 143: return 'R';
		case 40: return 'S';
		case 41: return 'T';
		case 145: return 'U';
		case 147: return 'V';
		case 215: return 'W';
		case 247: return 'X';
		case 43: return 'Y';
		case 45: return 'Z';
		case 44: return ';';
		case 171: return '!';
		case 178: return '?';
		case 61: return '\n';
		default: return 0;
		}
	} else {
		if (raw_key > 47 && raw_key < 58) return raw_key;
		switch (raw_key) {
		case 11: return 'a';
		case 13: return 'b';
		case 14: return 'c';
		case 15: return 'd';
		case 16: return 'e';
		case 18: return 'f';
		case 20: return 'g';
		case 22: return 'h';
		case 24: return 'i';
		case 26: return 'j';
		case 28: return 'k';
		case 29: return 'l';
		case 31: return 'm';
		case 129: return 'n';
		case 130: return 'o';
		case 131: return 'p';
		case 141: return 'q';
		case 143: return 'r';
		case 40: return 's';
		case 41: return 't';
		case 145: return 'u';
		case 147: return 'v';
		case 153: return KEY_DEL;
		case 155: return KEY_AC;
		case 215: return 'w';
		case 247: return 'x';
		case 43: return 'y';
		case 45: return 'z';
		case 44: return ',';
		case 171: return '.';
		case 178: return ' ';
		case 61: return '\n';
		default: return 0;
		}
	}
}


KeyPress Keyboard::coords_to_keypress(uint8_t x, uint8_t y, KeyState state)
{
	KeyPress keypress = KeyPress();
	keypress.shift = is_shift_active();
	keypress.alpha = is_alpha_active();
	keypress.key_raw = coords_to_key_raw(x, y);
	keypress.key_calculator = raw_key_to_calculator_key(keypress.key_raw, keypress.shift, keypress.alpha);
	keypress.key_keyboard = raw_key_to_keyboard_key(keypress.key_raw, keypress.shift, keypress.alpha);
	return keypress;
}


void Keyboard::set_pin(uint8_t pin)
{
	for (uint8_t i = 0; i < _outputs.size(); i++) {
		if (i == pin) gpio_set_dir(_outputs[i], GPIO_OUT);
		else gpio_set_dir(_outputs[i], GPIO_IN);
		gpio_put(_outputs[pin], 1);
	}
}

std::vector<bool> Keyboard::get_pins()
{
	std::vector<bool> ret = std::vector<bool>();
	for (auto& pin : _inputs) { ret.push_back(gpio_get(pin)); }
	return ret;
}

#endif