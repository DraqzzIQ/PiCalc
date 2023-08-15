#include "PicoKeyboard.h"
#ifdef PICO

PicoKeyboard::PicoKeyboard(WindowManager *window_manager) : IKeyboard(window_manager)
{
	for (auto & pin : outputs){
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);
	}

	for (auto & pin : inputs){
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_down(pin);
	}
}

bool PicoKeyboard::is_shift_active()
{
	return is_shift;
}

bool PicoKeyboard::is_alpha_active()
{
	return is_alpha;
}

void PicoKeyboard::check_for_keyboard_presses() {
	for (uint8_t px = 0; px < outputs.size(); px++){
		setPin(px);
		std::vector<bool> high_pins = getPins();
		for (uint8_t py = 0; py < high_pins.size(); py++){
			if (pressedButtons[px][py] && !high_pins[py]){
				pressedButtons[px][py] = false;
				_window_manager->handle_key_up(coords_to_keypress(px, py));
			}
			else if (!pressedButtons[px][py] && high_pins[py]){
				pressedButtons[px][py] = true;
				_window_manager->handle_key_down(coords_to_keypress(px, py));
			}
		}
	}
}

uint8_t PicoKeyboard::coords_to_keycode(uint8_t x, uint8_t y, bool raw = false){
	if (is_shift_active() && !raw) {
		switch(10*x + y){
		case 00: return Chars::KEY_MAP.at("shift");
		case 10: return Chars::KEY_MAP.at("alpha");
		}
	}
	else if(is_alpha_active() && !raw) {
		switch(10*x + y){
		case 00: return Chars::KEY_MAP.at("shift");
		case 10: return Chars::KEY_MAP.at("alpha");
		}
	}
	else {
		switch(10*x + y){
		case 00: return Chars::KEY_MAP.at("shift");
		case 10: return Chars::KEY_MAP.at("alpha");
		}
	}
}

KeyPress PicoKeyboard::coords_to_keypress(uint8_t x, uint8_t y){
	KeyPress keypress = KeyPress();
    keypress.key = coords_to_keycode(x, y);
	keypress.raw_key = coords_to_keycode(x, y, true);
    keypress.alpha = is_alpha_active();
    keypress.shift = is_shift_active();

	is_shift = false;
	is_alpha = false;
	if (keypress.raw_key = Chars::KEY_MAP.at("shift")) {
		is_shift = true;
	}
	if (keypress.raw_key = Chars::KEY_MAP.at("alpha")) {
		is_alpha = true;
	}
    return keypress;
}


void PicoKeyboard::setPin(uint8_t pin){
	for (uint8_t i = 0; i < outputs.size(); i++){
		if (i == pin) gpio_put(outputs[i], 1);
		else gpio_put(outputs[i], 0);
	}
}

std::vector<bool> PicoKeyboard::getPins(){
	std::vector<bool> ret = std::vector<bool>();
	for (auto & pin : inputs){
		ret.push_back(gpio_get(pin));
	}
	return ret;
}
#endif