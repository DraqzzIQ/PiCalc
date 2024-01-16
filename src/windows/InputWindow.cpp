#include "InputWindow.h"

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
			_finnished_callback(_input);
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
	std::cout << key << std::endl;
	return true;
}

void InputWindow::set_prompt(std::string prompt)
{
	_prompt = prompt;
}

void InputWindow::set_finnished_callback(std::function<void(std::string)> callback)
{
	_finnished_callback = callback;
}

std::string InputWindow::get_input()
{
	return _input;
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
    std::function<void(std::string)> callback = [](std::string input) {
        std::cout << input << std::endl;
		WindowManager::get_instance()->close_window();
    };
    InputWindow* in_win = new InputWindow();
    in_win->set_prompt(prompt);
    in_win->set_finnished_callback(callback);
    WindowManager::get_instance()->add_window(in_win);
    return in_win->get_input(); // TODO don't return until callback is called
}
