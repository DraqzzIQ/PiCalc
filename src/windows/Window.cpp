#include "windows/Window.h"

Window::Window():
	_frame(Frame(_window))
{
	clear_window();
}

Window::~Window() {}

Frame& Window::update_and_get_frame()
{
	update_window();
	return _frame;
}

void Window::update_window()
{
}

bool Window::handle_key_down(KeyPress keypress)
{
	return false;
}
bool Window::handle_key_up(KeyPress keypress)
{
	return false;
}

void Window::got_focus()
{
}

void Window::lost_focus()
{
}

void Window::clear_window()
{
	_window = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT + 1, false);
}

void Window::copy_frame(Frame& frame) const
{
	frame.corner_x = _frame.corner_x;
	frame.corner_y = _frame.corner_y;
	frame.screen_symbols = _frame.screen_symbols;
}

const Bitset2D& Window::get_window() const
{
	return _window;
}