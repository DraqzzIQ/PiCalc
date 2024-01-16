#include "InputWindow.h"

#ifdef PICO
IKeyboard* InputWindow::keyboard = new PicoKeyboard();
#else
IKeyboard* InputWindow::keyboard = new SDLKeyboard();
#endif

InputWindow::InputWindow()
{
	_blink_timer = Utils::us_since_boot();
}

InputWindow::~InputWindow()
{
}

Bitset2D InputWindow::update_window()
{
	clear_window();
	add_to_window(Graphics::create_text(_prompt), 1, 1);
	add_to_window(Graphics::create_text(_input), 1, 15);
	_rendered = add_cursor(window);
	return _rendered;
}
bool InputWindow::handle_key_down(KeyPress keypress)
{
	std::string key = Chars::KEY_MAP[keypress.key_keyboard];
	if (key == "ceil") {
		if (_input.length() > 0) {
			_finnished = true;
		}
	} else if (key == "DEL") {
		if (_cursor_index > 0) {
			_input = _input.substr(0, _input.length() - 1);
			_cursor_index--;
		}
	} else if (_input.length() >= 15) {
		return true;
	} else {
		_cursor_index++;
		_input += key;
	}
	return true;
}

void InputWindow::set_prompt(std::string prompt)
{
	_prompt = prompt;
}

std::string InputWindow::get_input()
{
	return _input;
}

bool InputWindow::get_finnished()
{
	return _finnished;
}

Bitset2D InputWindow::add_cursor(Bitset2D bitset)
{
	if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer += 500000;
		_cursor_on = !_cursor_on;
	}
	if (!_cursor_on || _cursor_index > 15) {
		return bitset;
	}
	for (uint32_t i = 0; i < 9; i++) {
		bitset.set_bit(_cursor_index*6 + 1, 15+i, true);
	}
	for (uint32_t i = 0; i < 9; i++) {
		bitset.set_bit(_cursor_index*6 + 2, 15+i, true);
	}
	return bitset;
}

std::string InputWindow::input(std::string prompt)
{
    InputWindow* in_win = new InputWindow();
    in_win->set_prompt(prompt);
    WindowManager::get_instance()->add_window(in_win);

	while (true) {
		InputWindow::keyboard->check_for_keyboard_presses();
		WindowManager::get_instance()->update();
		Utils::sleep_for_ms(10);
		if (in_win->get_finnished()) break;
	}
	WindowManager::get_instance()->close_window();
    return in_win->get_input();
}
