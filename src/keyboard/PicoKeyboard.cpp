#include "keyboard/PicoKeyboard.h"
#ifdef PICO

PicoKeyboard::PicoKeyboard(WindowManager* window_manager): IKeyboard(window_manager)
{
	stdio_init_all();

	for (auto& pin : outputs) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);
	}

	for (auto& pin : inputs) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_down(pin);
	}
}

bool PicoKeyboard::is_shift_active()
{
	return functionKeysState == KeyState::SHIFT_ON;
}

bool PicoKeyboard::is_alpha_active()
{
	return functionKeysState == KeyState::ALPHA_ON;
}

void PicoKeyboard::check_for_keyboard_presses()
{
	for (uint8_t px = 0; px < outputs.size(); px++) {
		setPin(px);
		sleep_ms(10);
		std::vector<bool> high_pins = getPins();
		for (uint8_t py = 0; py < high_pins.size(); py++) {
			if (pressedButtons[px][py] == KeyState::OFF && high_pins[py]) {
				KeyPress press = coords_to_keypress(px, py, functionKeysState);
				// printf("\nKey pressed:  "); // uncomment to test keys via picoprobe / serial output
				// print_key(press.key_calculator); // uncomment to test keys via picoprobe / serial output
				_window_manager->handle_key_down(press); // comment to test keys via picoprobe / serial output
				pressedButtons[px][py] = functionKeysState;

				if (press.key_raw == Chars::KEY_MAP.at("SHIFT")) functionKeysState = KeyState::SHIFT_ON;
				else if (press.key_raw == Chars::KEY_MAP.at("ALPHA")) functionKeysState = KeyState::ALPHA_ON;
				else functionKeysState = KeyState::ON;
			} else if (pressedButtons[px][py] != KeyState::OFF && !high_pins[py]) {
				KeyPress release = coords_to_keypress(px, py, pressedButtons[px][py]);
				// printf("\nKey released: "); // uncomment to test keys via picoprobe / serial output
				// print_key(release.key_calculator); // uncomment to test keys via picoprobe / serial output
				_window_manager->handle_key_up(release); // comment to test keys via picoprobe / serial output
				pressedButtons[px][py] = KeyState::OFF;
			}
		}
	}
}

void PicoKeyboard::print_key(uint8_t key)
{
	for (auto i = Chars::KEY_MAP.begin(); i != Chars::KEY_MAP.end(); i++) {
		if (i->second == key) { printf(i->first.c_str()); }
	}
}

uint8_t PicoKeyboard::coords_to_key_raw(uint8_t x, uint8_t y)
{
	switch (10 * x + y) {
	case 0: return Chars::KEY_MAP.at("SHIFT");
	case 1: return Chars::KEY_MAP.at("Abs");
	case 2: return Chars::KEY_MAP.at("fraction");
	case 3: return Chars::KEY_MAP.at("(-)");
	case 4: return Chars::KEY_MAP.at("RCL");
	case 5: return Chars::KEY_MAP.at("7");
	case 6: return Chars::KEY_MAP.at("4");
	case 7: return Chars::KEY_MAP.at("1");
	case 8: return Chars::KEY_MAP.at("0");
	case 10: return Chars::KEY_MAP.at("ALPHA");
	case 11: return Chars::KEY_MAP.at("x^3");
	case 12: return Chars::KEY_MAP.at("root2");
	case 13: return Chars::KEY_MAP.at("time");
	case 14: return Chars::KEY_MAP.at("ENG");
	case 15: return Chars::KEY_MAP.at("8");
	case 16: return Chars::KEY_MAP.at("5");
	case 17: return Chars::KEY_MAP.at("2");
	case 18: return Chars::KEY_MAP.at(",");
	case 20: return Chars::KEY_MAP.at("left");
	case 21: return Chars::KEY_MAP.at("down");
	case 22: return Chars::KEY_MAP.at("x^2");
	case 23: return Chars::KEY_MAP.at("hyp");
	case 24: return Chars::KEY_MAP.at("(");
	case 25: return Chars::KEY_MAP.at("9");
	case 26: return Chars::KEY_MAP.at("6");
	case 27: return Chars::KEY_MAP.at("3");
	case 28: return Chars::KEY_MAP.at("*10^n");
	case 30: return Chars::KEY_MAP.at("right");
	case 31: return Chars::KEY_MAP.at("x^-1");
	case 32: return Chars::KEY_MAP.at("x^n");
	case 33: return Chars::KEY_MAP.at("sin");
	case 34: return Chars::KEY_MAP.at(")");
	case 35: return Chars::KEY_MAP.at("DEL");
	case 36: return Chars::KEY_MAP.at("multiply");
	case 37: return Chars::KEY_MAP.at("+");
	case 38: return Chars::KEY_MAP.at("Ans");
	case 40: return Chars::KEY_MAP.at("up");
	case 41: return Chars::KEY_MAP.at("logn");
	case 42: return Chars::KEY_MAP.at("log10");
	case 43: return Chars::KEY_MAP.at("cos");
	case 44: return Chars::KEY_MAP.at("S<>D");
	case 45: return Chars::KEY_MAP.at("AC");
	case 46: return Chars::KEY_MAP.at("divide");
	case 47: return Chars::KEY_MAP.at("-");
	case 48: return Chars::KEY_MAP.at("=");
	case 50: return Chars::KEY_MAP.at("MODE");
	case 52: return Chars::KEY_MAP.at("ln");
	case 53: return Chars::KEY_MAP.at("tan");
	case 54: return Chars::KEY_MAP.at("M+");
	default: return Chars::KEY_MAP.at("unknown");
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


void PicoKeyboard::setPin(uint8_t pin)
{
	for (uint8_t i = 0; i < outputs.size(); i++) {
		if (i == pin) gpio_set_dir(outputs[i], GPIO_OUT);
		else gpio_set_dir(outputs[i], GPIO_IN);
		gpio_put(outputs[pin], 1);
	}
}

std::vector<bool> PicoKeyboard::getPins()
{
	std::vector<bool> ret = std::vector<bool>();
	for (auto& pin : inputs) { ret.push_back(gpio_get(pin)); }
	return ret;
}
#endif