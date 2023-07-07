#include "Window.h"

Window::Window()
{
	corner_x = 0;
	corner_y = 0;
	clear_window();
}

Window::~Window()
{
}

render_plane Window::get_render_canvas()
{
	render_plane canvas;

	for (size_t i = 0; i < SCREEN_WIDTH; i++)
	{
		std::vector<bool> row;

		for (size_t j = 0; j < SCREEN_HEIGHT; j++)
		{
			row.push_back(canvas[corner_y +i][corner_x + j]);
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
		for (size_t i = 0; i < window.size(); i++) {
			window[i].insert(window[i].end(), empty.begin(), empty.end());
		}
	}

	for (size_t i = 0; i < graphic.size(); i++) {
		std::copy(std::begin(graphic[i]), std::end(graphic[i]), std::begin(window[i + c_x]) + c_y);
	}
}

void Window::clear_window() {
	window = render_plane(SCREEN_WIDTH, std::vector<bool>(SCREEN_HEIGHT, false));
}