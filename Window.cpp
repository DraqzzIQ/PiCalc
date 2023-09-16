#include "Window.h"

Window::Window()
{
	clear_window();
	clear_symbols();
}

Window::~Window()
{
}

render_plane Window::update_window()
{
    return get_render_canvas();
}

render_plane Window::get_render_canvas()
{
	render_plane canvas;

	for (std::size_t i = 0; i < SCREEN_WIDTH; i++)
	{
		dynamic_bitset column = dynamic_bitset(SCREEN_HEIGHT, false);

		for (std::size_t j = 0; j < SCREEN_HEIGHT; j++)
		{
			if(corner_x + i < window.size() && corner_y + j < window[corner_x + i].size())
				column.set(j, (window[corner_x + i][corner_y + j]));
		}
		canvas.push_back(column);
	}
	return canvas;
}

void Window::add_to_window(render_plane graphic, int corner_x, int corner_y) {
	//make sure the graphic fits x-wise
	if (graphic.size() + corner_x > window.size()) {
		dynamic_bitset empty = dynamic_bitset(window[0].size(), false);
		while (graphic.size() + corner_x > window.size()) {
			window.push_back(empty);
		}
	}
	//make sure the graphic fits y-wise
	if (graphic[0].size() + corner_y > window[0].size()) {
		dynamic_bitset empty = dynamic_bitset(graphic[0].size() + corner_y - window[0].size(), false);
		for (std::size_t i = 0; i < window.size(); i++) {
			window[i].insert(window[i].size(), empty);
		}
	}

	for (std::size_t i = 0; i < graphic.size(); i++) {
		window[i + corner_x].set(corner_y, graphic[i]);
	}
}

void Window::clear_window() {
	window = render_plane(SCREEN_WIDTH, dynamic_bitset(SCREEN_HEIGHT, false));
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
	if(corner_x + SCREEN_WIDTH < window.size())
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