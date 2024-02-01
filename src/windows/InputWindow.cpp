#include "InputWindow.h"


InputWindow::InputWindow(const std::string& promt, std::function<void(std::string&)> callback)
{
	_blink_timer = Utils::us_since_boot();
	_prompt = promt;
	_callback = callback;
}

InputWindow::~InputWindow()
{
}

void InputWindow::update_window()
{
	clear_window();
	_window.put_chars(1, 1, Graphics::SYMBOLS_9_HIGH, _prompt, false);
	_window.put_chars(1, 15, Graphics::SYMBOLS_9_HIGH, _input, false);
	add_cursor(_window);
}

bool InputWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_keyboard == '\n') {
		if (_input.size() > 0) {
			WindowManager::get_instance()->close_window(false);
			_callback(_input);
			delete this;
		}
	} else if (keypress.key_keyboard == KEY_DEL) {
		if (_cursor_index > 0) {
			_input.pop_back();
			_cursor_index--;
			_cursor_on = true;
			_blink_timer = Utils::us_since_boot();
		}
	} else if (keypress.key_keyboard > 6 && _input.size() < 15) {
		_cursor_index++;
		_input.push_back(keypress.key_keyboard);
		_cursor_on = true;
		_blink_timer = Utils::us_since_boot();
	}
	return true;
}

void InputWindow::add_cursor(Bitset2D& bitset)
{
	if (Utils::us_since_boot() > _blink_timer + 500000) {
		_blink_timer += 500000;
		_cursor_on = !_cursor_on;
	}
	if (!_cursor_on || _cursor_index > 15) return;
	_window.draw_vertical_line(_cursor_index * 6, 15, 9, true);
	_window.draw_vertical_line(_cursor_index * 6 + 1, 15, 9, true);
}

void InputWindow::input(const std::string& promt, std::function<void(std::string&)> callback)
{
	WindowManager::get_instance()->add_window(new InputWindow(promt, callback));
}