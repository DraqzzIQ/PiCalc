#include "PicoKeyboard.h"
#ifdef PICO

PicoKeyboard::PicoKeyboard(WindowManager *window_manager) : IKeyboard(window_manager)
{
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
	
}
#endif