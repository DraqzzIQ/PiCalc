#include "windows/TextWindow.h"

// TODO: marking/copying/pasting text, fix line error at the bottom of the display (only on pico)

TextWindow::TextWindow()
{
	_frame.corner_y = 0;
	i = 0;
}

void TextWindow::update_window()
{
	//_window = _text.get_rendered_equation();
	clear_window();
	_window.put_number_aligned_right(94, 20, Graphics::SYMBOLS_9_HIGH, i);
	if (Graphics::SYMBOLS_6_HIGH.contains(i)) {
		_window.set(0, 0, Graphics::SYMBOLS_6_HIGH.at(i), false);
	}
}

bool TextWindow::handle_key_down(KeyPress keypress)
{
	// if (handle_key_down_special(keypress)) return true;
	// if (keypress.alpha && keypress.key_raw == '=') {
	//	_calculator_keyboard = !_calculator_keyboard;
	//	_frame.set_screen_symbol(15, _calculator_keyboard);
	// } else if (_calculator_keyboard) {
	//	if (keypress.key_calculator != 0) _text.handle_key_down(keypress.key_calculator);
	// } else {
	//	// handle font changes
	//	if (keypress.shift && keypress.key_raw > 47 && keypress.key_raw < 58) keypress.key_keyboard = keypress.key_raw + 159;
	//	if (keypress.key_keyboard != 0) _text.handle_key_down(keypress.key_keyboard);
	// }
	i++;
	return true;
}

bool TextWindow::handle_key_up(KeyPress keypress)
{
	return true;
}

bool TextWindow::handle_key_down_special(KeyPress keypress)
{
	return false;
}