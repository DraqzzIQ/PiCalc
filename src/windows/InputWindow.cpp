#include "InputWindow.h"


InputWindow::InputWindow(std::string promt, std::function<void(std::string)> callback)
{
	_blink_timer = Utils::us_since_boot();
	_prompt = promt;
	_callback = callback;
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
			WindowManager::get_instance()->close_window(false);
			_callback(_input);
			delete this;
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
		bitset.set_bit(_cursor_index * 6 + 1, 15 + i, true);
	}
	for (uint32_t i = 0; i < 9; i++) {
		bitset.set_bit(_cursor_index * 6 + 2, 15 + i, true);
	}
	return bitset;
}

void InputWindow::input(std::string promt, std::function<void(std::string)> callback)
{
	WindowManager::get_instance()->add_window(new InputWindow(promt, callback));
}