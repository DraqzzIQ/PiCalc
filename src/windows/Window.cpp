#include "windows/Window.h"

Window::Window()
{
	clear_window();
	clear_symbols();
}

Window::~Window() {}

Bitset2D Window::update_window()
{
	return get_render_canvas();
}

// TODO: replace with get()
Bitset2D Window::get_render_canvas()
{
	Bitset2D canvas;

	for (uint32_t i = 0; i < SCREEN_WIDTH; i++) {
		DynamicBitset column(SCREEN_HEIGHT, false);

		for (uint32_t j = 0; j < SCREEN_HEIGHT; j++) {
			if (corner_x + i < window.width() && corner_y + j < window.height()) column.set(j, (window[corner_x + i][corner_y + j]));
		}
		canvas.push_back(column);
	}
	return canvas;
}

void Window::add_to_window(const Bitset2D& graphic, int corner_x, int corner_y)
{
	window.set(corner_x, corner_y, graphic, true);
}

void Window::clear_window()
{
	window = Bitset2D(SCREEN_WIDTH, DynamicBitset(SCREEN_HEIGHT, false));
}

void Window::clear_symbols()
{
	screen_symbols = DynamicBitset(Graphics::SCREEN_SYMBOLS.size(), false);
}

void Window::change_symbol(std::string symbol, bool state)
{
	screen_symbols.set(std::find(Graphics::SCREEN_SYMBOLS.begin(), Graphics::SCREEN_SYMBOLS.end(), symbol) - Graphics::SCREEN_SYMBOLS.begin(), state);
}

void Window::scroll_left()
{
	if (corner_x > 0) corner_x -= SCREEN_WIDTH;
}

void Window::scroll_right()
{
	if (corner_x + SCREEN_WIDTH < window.width()) corner_x += SCREEN_WIDTH;
}

void Window::handle_key_down(KeyPress keypress) {}
void Window::handle_key_up(KeyPress keypress) {}

void Window::got_focus() {}

void Window::lost_focus() {}
