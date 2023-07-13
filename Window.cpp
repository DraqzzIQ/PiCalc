#include "Window.h"
#include "Graphics.h"
#include <algorithm>

Window::Window()
{
	corner_x = 0;
	corner_y = 0;
	clear_window();
	clear_symbols();
	change_Symbol("Math", true);
}

Window::~Window()
{
}

render_plane Window::get_render_canvas()
{
	render_plane canvas;

	for (std::size_t i = 0; i < SCREEN_WIDTH; i++)
	{
		std::vector<bool> row = std::vector<bool>(SCREEN_HEIGHT + 1,false);

		for (std::size_t j = 0; j < SCREEN_HEIGHT + 1; j++)
		{
			if(corner_x + i < window.size() && corner_y + j < window[corner_x + i].size())
				row[j] = (window[corner_x + i][corner_y + j]);
		}
		canvas.push_back(row);
	}
	return canvas;
}

void Window::add_to_window(render_plane graphic, int c_x, int c_y) {
	if (graphic.size() + c_x > window.size()) {
		std::vector<bool> empty = std::vector<bool>(window[0].size(), false);
		while (graphic.size() + c_x > window.size()) {
			window.push_back(empty);
		}
	}
	if (graphic[0].size() + c_y > window[0].size()) {
		std::vector<bool> empty = std::vector<bool>(graphic[0].size() + c_y - window[0].size(), false);
		for (std::size_t i = 0; i < window.size(); i++) {
			window[i].insert(window[i].end(), empty.begin(), empty.end());
		}
	}

	for (std::size_t i = 0; i < graphic.size(); i++) {
		std::copy(std::begin(graphic[i]), std::end(graphic[i]), std::begin(window[i + c_x]) + c_y);
	}
}

void Window::clear_window() {
	window = render_plane(SCREEN_WIDTH, std::vector<bool>(SCREEN_HEIGHT, false));
}

void Window::clear_symbols() {
	screen_symbols = std::vector<bool>(Graphics::ScreenSymbols.size(), false);
}

void Window::change_Symbol(std::string symbol, bool state) {
	screen_symbols[std::find(Graphics::ScreenSymbols.begin(), Graphics::ScreenSymbols.end(), symbol) - Graphics::ScreenSymbols.begin()] = state;
}