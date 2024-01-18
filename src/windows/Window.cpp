#include "windows/Window.h"
#include "Window.h"

Window::Window()
{
	clear_window();
	clear_symbols();
}

Window::~Window() {}

Frame Window::update_window()
{
	return Frame(get_render_canvas(), _screen_symbols);
}

// TODO: replace with get()
Bitset2D Window::get_render_canvas()
{
	Bitset2D canvas;

	for (uint32_t i = 0; i < SCREEN_WIDTH; i++) {
		DynamicBitset column(SCREEN_HEIGHT, false);

		for (uint32_t j = 0; j < SCREEN_HEIGHT; j++) {
			if (_corner_x + i < _window.width() && _corner_y + j < _window.height()) column.set(j, (_window[_corner_x + i][_corner_y + j]));
		}
		canvas.push_back(column);
	}
	return canvas;
}

void Window::add_to_window(const Bitset2D& graphic, int corner_x, int corner_y)
{
	_window.set(corner_x, corner_y, graphic, true);
}

void Window::clear_window()
{
	_window = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

void Window::clear_symbols()
{
	_screen_symbols = DynamicBitset(Graphics::SCREEN_SYMBOLS.size(), false);
}

void Window::change_symbol(std::string symbol, bool state)
{
	_screen_symbols.set(std::find(Graphics::SCREEN_SYMBOLS.begin(), Graphics::SCREEN_SYMBOLS.end(), symbol) - Graphics::SCREEN_SYMBOLS.begin(), state);
}

void Window::scroll_left()
{
	if (_corner_x > 0) _corner_x -= SCREEN_WIDTH;
}

void Window::scroll_right()
{
	if (_corner_x + SCREEN_WIDTH < _window.width()) _corner_x += SCREEN_WIDTH;
}

bool Window::handle_key_down(KeyPress keypress)
{
	return false;
}
bool Window::handle_key_up(KeyPress keypress)
{
	return false;
}

Bitset2D Window::get_preview()
{
	return _window;
}

void Window::got_focus() {}

void Window::lost_focus() {}