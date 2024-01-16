#include "InputWindow.h"

InputWindow::InputWindow()
{
}

InputWindow::~InputWindow()
{
}

Bitset2D InputWindow::update_window()
{
	clear_window();
	add_to_window(Graphics::create_text(_prompt), 1, 1);
	add_to_window(Graphics::create_text(_input), 1, 15);
	return window;
}
bool InputWindow::handle_key_down(KeyPress keypress)
{
	std::string key = Chars::KEY_MAP[keypress.key_keyboard];
	std::cout << key << std::endl;
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
