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
		std::vector<bool> row = std::vector<bool>(SCREEN_HEIGHT,false);

		for (std::size_t j = 0; j < SCREEN_HEIGHT; j++)
		{
			if(corner_x + i < window.size() && corner_y + j < window[corner_x + i].size())
				row[j] = (window[corner_x + i][corner_y + j]);
		}
		canvas.push_back(row);
	}
	return canvas;
}

void Window::add_to_window(render_plane graphic, int corner_x, int corner_y) {
	//make sure the graphic fits x-wise
	if (graphic.size() + corner_x > window.size()) {
		std::vector<bool> empty = std::vector<bool>(window[0].size(), false);
		while (graphic.size() + corner_x > window.size()) {
			window.push_back(empty);
		}
	}
	//make sure the graphic fits y-wise
	if (graphic[0].size() + corner_y > window[0].size()) {
		std::vector<bool> empty = std::vector<bool>(graphic[0].size() + corner_y - window[0].size(), false);
		for (std::size_t i = 0; i < window.size(); i++) {
			window[i].insert(window[i].end(), empty.begin(), empty.end());
		}
	}

	for (std::size_t i = 0; i < graphic.size(); i++) {
		std::copy(std::begin(graphic[i]), std::end(graphic[i]), std::begin(window[i + corner_x]) + corner_y);
	}
}

void Window::clear_window() {
	window = render_plane(SCREEN_WIDTH, std::vector<bool>(SCREEN_HEIGHT, false));
}

void Window::clear_symbols() {
	screen_symbols = std::vector<bool>(Graphics::SCREEN_SYMBOLS.size(), false);
}

void Window::change_symbol(std::string symbol, bool state) {
	screen_symbols[std::find(Graphics::SCREEN_SYMBOLS.begin(), Graphics::SCREEN_SYMBOLS.end(), symbol) - Graphics::SCREEN_SYMBOLS.begin()] = state;
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