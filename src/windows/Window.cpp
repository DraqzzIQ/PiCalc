#include "windows/Window.h"
#include "Window.h"

Window::Window()
{
	clear_window();
}

Window::~Window() {}

Frame Window::update_window()
{
	return Frame(get_render_canvas());
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

Bitset2D Window::get_render_canvas()
{
	if (_corner_x = 0 && _corner_y == 0) {
		if (_window.width() < SCREEN_WIDTH || _window.height() < SCREEN_HEIGHT) {
			Bitset2D canvas = _window;
			canvas.extend_down(SCREEN_HEIGHT - _window.height(), false);
			canvas.extend_right(SCREEN_WIDTH - _window.width(), false);
			return canvas;
		} else return _window;
	}

	Bitset2D canvas;
	_window.copy(_corner_x, _corner_y, SCREEN_WIDTH, SCREEN_HEIGHT, canvas);
	if (canvas.width() < SCREEN_WIDTH) canvas.extend_right(SCREEN_WIDTH - canvas.width(), false);
	if (canvas.height() < SCREEN_HEIGHT) canvas.extend_down(SCREEN_HEIGHT - canvas.height(), false);
	return canvas;
}

void Window::add_to_window(const Bitset2D& graphic, int corner_x, int corner_y)
{
	_window.set(corner_x, corner_y, graphic, true);
}

void Window::put_text(KEY_SET text, FONT font, int corner_x, int corner_y)
{
	_window.put_chars(corner_x, corner_y, font, text, true);
}

void Window::put_text(std::string text, FONT font, int corner_x, int corner_y)
{
	_window.put_chars(corner_x, corner_y, font, text, true);
}

void Window::clear_window()
{
	_window = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

void Window::scroll_left()
{
	if (_corner_x > 0) _corner_x -= SCREEN_WIDTH;
}

void Window::scroll_right()
{
	if (_corner_x + SCREEN_WIDTH < _window.width()) _corner_x += SCREEN_WIDTH;
}

Bitset2D Window::get_preview()
{
	return _window;
}
