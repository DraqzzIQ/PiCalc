#include "windows/Window.h"
#include "Window.h"

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
	_window = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

const Bitset2D& Window::get_preview()
{
	return _window;
}