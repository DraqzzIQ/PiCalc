#include "Window.h"
#include <algorithm>

Window::Window()
{
	corner_x = 0;
	corner_y = 0;
	clearPixels();
}

Window::~Window()
{

}

render_plane Window::get_render_window()
{
	render_plane render_plane;

	for (size_t i = 0; i < SCREEN_WIDTH; i++)
	{
		std::vector<bool> row;

		for (size_t j = 0; j < SCREEN_HEIGHT; j++)
		{
			row.push_back(pixels[corner_y +i][corner_x + j]);
		}

		render_plane.push_back(row);
	}

	return render_plane;
}


/// <summary>
/// Adds a Graphic in form of a renderPlane (like Text) at given Coordinates to the Screen
/// </summary>
/// <param name="renderplane"></param>
/// <param name="c_x"></param>
/// <param name="c_y"></param>
void Window::addToPixels(render_plane renderplane, int c_x, int c_y) {
	if (renderplane.size() + c_x > pixels.size()) {
		std::vector<bool> empty = std::vector<bool>(pixels[0].size(), false);
		while (renderplane.size() + c_x > pixels.size()) {
			pixels.push_back(empty);
		}
	}
	if (renderplane[0].size() + c_y > pixels[0].size()) {
		std::vector<bool> empty = std::vector<bool>(renderplane[0].size() + c_y - pixels[0].size(), false);
		for (int i = 0; i < pixels.size(); i++) {
			pixels[i].insert(pixels[i].end(), empty.begin(), empty.end());
		}
	}

	for (int i = 0; i < renderplane.size(); i++) {
		std::copy(std::begin(renderplane[i]), std::end(renderplane[i]), std::begin(pixels[i + c_x]) + c_y);
	}
}

void Window::clearPixels() {
	pixels = render_plane(SCREEN_WIDTH, std::vector<bool>(SCREEN_HEIGHT, false));
}