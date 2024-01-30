#include "keyboard/PicoKeyboard.h"
#ifdef PICO

PicoKeyboard::PicoKeyboard():
	IKeyboard()
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

bool PicoKeyboard::is_shift_active()
{
	return _function_keys_state == KeyState::SHIFT_ON;
}

bool PicoKeyboard::is_alpha_active()
{
	return _function_keys_state == KeyState::ALPHA_ON;
}

void PicoKeyboard::check_for_keyboard_presses()
{
	for (uint8_t px = 0; px < _outputs.size(); px++) {
		set_pin(px);
		sleep_ms(10);
		std::vector<bool> high_pins = get_pins();
		for (uint8_t py = 0; py < high_pins.size(); py++) {
			if (_pressed_buttons[px][py] == KeyState::OFF && high_pins[py]) {
				KeyPress press = coords_to_keypress(px, py, _function_keys_state);
				// std::cout << "\nKey pressed: " << unsigned(press.key_calculator) << std::endl; // uncomment to test keys via picoprobe / serial output
				_window_manager->handle_key_down(press); // comment to test keys via picoprobe / serial output
				_pressed_buttons[px][py] = _function_keys_state;

				if (press.key_raw == 1) _function_keys_state = KeyState::SHIFT_ON;
				else if (press.key_raw == 2) _function_keys_state = KeyState::ALPHA_ON;
				else _function_keys_state = KeyState::ON;
			} else if (_pressed_buttons[px][py] != KeyState::OFF && !high_pins[py]) {
				KeyPress release = coords_to_keypress(px, py, _pressed_buttons[px][py]);
				// std::cout << "\nKey released: " << unsigned(release.key_calculator) << std::endl; // uncomment to test keys via picoprobe / serial output
				_window_manager->handle_key_up(release); // comment to test keys via picoprobe / serial output
				_pressed_buttons[px][py] = KeyState::OFF;
			}
		}
	}
}

KEY PicoKeyboard::coords_to_key_raw(uint8_t x, uint8_t y)
{
	switch (10 * x + y) {
	case 0: return 1;
	case 1: return 11;
	case 2: return 16;
	case 3: return 28;
	case 4: return 141;
	case 5: return 55;
	case 6: return 52;
	case 7: return 49;
	case 8: return 48;
	case 10: return 2;
	case 11: return 13;
	case 12: return 18;
	case 13: return 29;
	case 14: return 143;
	case 15: return 56;
	case 16: return 53;
	case 17: return 50;
	case 18: return 44;
	case 20: return 5;
	case 21: return 4;
	case 22: return 20;
	case 23: return 31;
	case 24: return 40;
	case 25: return 57;
	case 26: return 54;
	case 27: return 51;
	case 28: return 171;
	case 30: return 3;
	case 31: return 14;
	case 32: return 22;
	case 33: return 129;
	case 34: return 41;
	case 35: return 153;
	case 36: return 215;
	case 37: return 43;
	case 38: return 178;
	case 40: return 6;
	case 41: return 15;
	case 42: return 24;
	case 43: return 130;
	case 44: return 145;
	case 45: return 155;
	case 46: return 247;
	case 47: return 45;
	case 48: return 61;
	case 50: return 7;
	case 52: return 26;
	case 53: return 131;
	case 54: return 147;
	default: return 0;
	}
}

KEY PicoKeyboard::raw_key_to_keyboard_key(KEY raw_key, bool shift, bool alpha)
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
		case 153: return 153; // DEL
		case 155: return 155; // AC
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


KeyPress PicoKeyboard::coords_to_keypress(uint8_t x, uint8_t y, KeyState state)
{
	KeyPress keypress = KeyPress();
	keypress.shift = is_shift_active();
	keypress.alpha = is_alpha_active();
	keypress.key_raw = coords_to_key_raw(x, y);
	keypress.key_calculator = raw_key_to_calculator_key(keypress.key_raw, keypress.shift, keypress.alpha);
	keypress.key_keyboard = raw_key_to_keyboard_key(keypress.key_raw, keypress.shift, keypress.alpha);
	return keypress;
}


void PicoKeyboard::set_pin(uint8_t pin)
{
	for (uint8_t i = 0; i < _outputs.size(); i++) {
		if (i == pin) gpio_set_dir(_outputs[i], GPIO_OUT);
		else gpio_set_dir(_outputs[i], GPIO_IN);
		gpio_put(_outputs[pin], 1);
	}
}

std::vector<bool> PicoKeyboard::get_pins()
{
	std::vector<bool> ret = std::vector<bool>();
	for (auto& pin : _inputs) { ret.push_back(gpio_get(pin)); }
	return ret;
}
#endif
