#include "keyboard/PicoKeyboard.h"
#ifdef PICO

PicoKeyboard* PicoKeyboard::_instance = nullptr;

PicoKeyboard* PicoKeyboard::get_instance()
{
	if (!_instance)
		_instance = new PicoKeyboard();

	return _instance;
}

PicoKeyboard::PicoKeyboard():
	IKeyboard()
{
	gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &PicoKeyboard::interrupt_callback);


	for (uint8_t pin : _outputs) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);
		gpio_put(pin, 1);
	}

	for (uint8_t pin : _inputs) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_down(pin);
		gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
	}
}

PicoKeyboard::~PicoKeyboard()
{
}

bool PicoKeyboard::is_shift_active()
{
	return _function_keys_state == KeyState::SHIFT_ON;
}

bool PicoKeyboard::is_alpha_active()
{
	return _function_keys_state == KeyState::ALPHA_ON;
}

void PicoKeyboard::interrupt_callback(uint gpio, uint32_t events)
{
	PicoKeyboard::get_instance()->button_pressed(gpio, events);
}

void PicoKeyboard::button_pressed(uint interrupt_pin, uint32_t events)
{
	gpio_set_irq_enabled(interrupt_pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false); // disable interrupts to prevent retriggering
	set_pins(0);

	for (uint8_t output_pin = 0; output_pin < _outputs.size(); output_pin++) {
		gpio_put(_outputs[output_pin], 1);
		while (!gpio_get(_outputs[output_pin])) {} // wait for output to be high
		bool interrupt_pin_high = gpio_get(interrupt_pin);

		if (_pressed_buttons[output_pin][interrupt_pin] == KeyState::OFF && interrupt_pin_high) {
			KeyPress press = coords_to_keypress(output_pin, interrupt_pin, _function_keys_state);
			_window_manager->handle_key_down(press);
			_pressed_buttons[output_pin][interrupt_pin] = _function_keys_state;

			if (press.key_raw == Chars::CHAR_TO_KEYCODE.at("SHIFT")) _function_keys_state = KeyState::SHIFT_ON;
			else if (press.key_raw == Chars::CHAR_TO_KEYCODE.at("ALPHA")) _function_keys_state = KeyState::ALPHA_ON;
			else _function_keys_state = KeyState::ON;
		} else if (_pressed_buttons[output_pin][interrupt_pin] != KeyState::OFF && !interrupt_pin_high) {
			KeyPress release = coords_to_keypress(output_pin, interrupt_pin, _function_keys_state);
			_window_manager->handle_key_up(release);
			_pressed_buttons[output_pin][interrupt_pin] = KeyState::OFF;
		}

		gpio_put(_outputs[output_pin], 0);
	}

	set_pins(1);
	gpio_set_irq_enabled(interrupt_pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true); // reenable interrupts
}

void PicoKeyboard::print_key(KEY key)
{
	for (int i = 0; i < Chars::KEY_MAP.size(); i++) {
		if (i == key) { std::cout << Chars::KEY_MAP[i] << std::endl; }
	}
}

KEY PicoKeyboard::coords_to_key_raw(uint8_t x, uint8_t y)
{
	switch (10 * x + y) {
	case 0: return Chars::CHAR_TO_KEYCODE.at("SHIFT");
	case 1: return Chars::CHAR_TO_KEYCODE.at("Abs");
	case 2: return Chars::CHAR_TO_KEYCODE.at("fraction");
	case 3: return Chars::CHAR_TO_KEYCODE.at("(-)");
	case 4: return Chars::CHAR_TO_KEYCODE.at("RCL");
	case 5: return Chars::CHAR_TO_KEYCODE.at("7");
	case 6: return Chars::CHAR_TO_KEYCODE.at("4");
	case 7: return Chars::CHAR_TO_KEYCODE.at("1");
	case 8: return Chars::CHAR_TO_KEYCODE.at("0");
	case 10: return Chars::CHAR_TO_KEYCODE.at("ALPHA");
	case 11: return Chars::CHAR_TO_KEYCODE.at("x^3");
	case 12: return Chars::CHAR_TO_KEYCODE.at("root2");
	case 13: return Chars::CHAR_TO_KEYCODE.at("time");
	case 14: return Chars::CHAR_TO_KEYCODE.at("ENG");
	case 15: return Chars::CHAR_TO_KEYCODE.at("8");
	case 16: return Chars::CHAR_TO_KEYCODE.at("5");
	case 17: return Chars::CHAR_TO_KEYCODE.at("2");
	case 18: return Chars::CHAR_TO_KEYCODE.at(",");
	case 20: return Chars::CHAR_TO_KEYCODE.at("left");
	case 21: return Chars::CHAR_TO_KEYCODE.at("down");
	case 22: return Chars::CHAR_TO_KEYCODE.at("x^2");
	case 23: return Chars::CHAR_TO_KEYCODE.at("hyp");
	case 24: return Chars::CHAR_TO_KEYCODE.at("(");
	case 25: return Chars::CHAR_TO_KEYCODE.at("9");
	case 26: return Chars::CHAR_TO_KEYCODE.at("6");
	case 27: return Chars::CHAR_TO_KEYCODE.at("3");
	case 28: return Chars::CHAR_TO_KEYCODE.at("*10^n");
	case 30: return Chars::CHAR_TO_KEYCODE.at("up");
	case 31: return Chars::CHAR_TO_KEYCODE.at("x^-1");
	case 32: return Chars::CHAR_TO_KEYCODE.at("x^n");
	case 33: return Chars::CHAR_TO_KEYCODE.at("sin");
	case 34: return Chars::CHAR_TO_KEYCODE.at(")");
	case 35: return Chars::CHAR_TO_KEYCODE.at("DEL");
	case 36: return Chars::CHAR_TO_KEYCODE.at("multiply");
	case 37: return Chars::CHAR_TO_KEYCODE.at("+");
	case 38: return Chars::CHAR_TO_KEYCODE.at("Ans");
	case 40: return Chars::CHAR_TO_KEYCODE.at("right");
	case 41: return Chars::CHAR_TO_KEYCODE.at("logn");
	case 42: return Chars::CHAR_TO_KEYCODE.at("log10");
	case 43: return Chars::CHAR_TO_KEYCODE.at("cos");
	case 44: return Chars::CHAR_TO_KEYCODE.at("S<>D");
	case 45: return Chars::CHAR_TO_KEYCODE.at("AC");
	case 46: return Chars::CHAR_TO_KEYCODE.at("divide");
	case 47: return Chars::CHAR_TO_KEYCODE.at("-");
	case 48: return Chars::CHAR_TO_KEYCODE.at("=");
	case 50: return Chars::CHAR_TO_KEYCODE.at("MODE");
	case 52: return Chars::CHAR_TO_KEYCODE.at("ln");
	case 53: return Chars::CHAR_TO_KEYCODE.at("tan");
	case 54: return Chars::CHAR_TO_KEYCODE.at("M+");
	default: return Chars::CHAR_TO_KEYCODE.at("unknown");
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

void PicoKeyboard::set_pins(bool value)
{
	for (uint8_t pin : _outputs) {
		gpio_put(pin, value);
	}
}
#endif