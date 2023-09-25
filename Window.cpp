#include "Window.h"

Window::Window()
{
	clear_window();
	clear_symbols();
}

Window::~Window()
{
}

bitset_2d Window::update_window()
{
    return get_render_canvas();
}

//TODO: replace with get()
bitset_2d Window::get_render_canvas()
{
	bitset_2d canvas;

	for (std::size_t i = 0; i < SCREEN_WIDTH; i++)
	{
		dynamic_bitset column(SCREEN_HEIGHT, false);

		for (std::size_t j = 0; j < SCREEN_HEIGHT; j++)
		{
			if(corner_x + i < window.width() && corner_y + j < window.height())
				column.set(j, (window[corner_x + i][corner_y + j]));
		}
		canvas.push_back(column);
	}
	return canvas;
}

void Window::add_to_window(const bitset_2d& graphic, int corner_x, int corner_y) {
	window.set(corner_x, corner_y, graphic, true);
}

void Window::clear_window() {
	window = bitset_2d(SCREEN_WIDTH, dynamic_bitset(SCREEN_HEIGHT, false));
}

void Window::clear_symbols() {
	screen_symbols = dynamic_bitset(Graphics::SCREEN_SYMBOLS.size(), false);
}

void Window::change_symbol(std::string symbol, bool state) {
	screen_symbols.set(std::find(Graphics::SCREEN_SYMBOLS.begin(), Graphics::SCREEN_SYMBOLS.end(), symbol) - Graphics::SCREEN_SYMBOLS.begin(), state);
}

void Window::scroll_left()
{
	if(corner_x > 0)
		corner_x -= SCREEN_WIDTH;
}

void Window::scroll_right()
{
	if(corner_x + SCREEN_WIDTH < window.width())
		corner_x += SCREEN_WIDTH;
}

void Window::handle_key_down(KeyPress keypress) {

}
void Window::handle_key_up(KeyPress keypress) {

}

void Window::got_focus() {

}

void Window::lost_focus() {

}