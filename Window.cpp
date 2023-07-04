#include "Window.h"

Window::Window()
{
	corner_x = 0;
	corner_y = 0;
	pixels = std::vector<std::vector<bool>>(SCREEN_HEIGHT, std::vector<bool>(SCREEN_WIDTH, false));
}

std::vector<std::vector<bool>> Window::get_render_window()
{
	std::vector<std::vector<bool>> render_window;

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		std::vector<bool> row;

		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			row.push_back(pixels[corner_y +i][corner_x + j]);
		}

		render_window.push_back(row);
	}

	return render_window;
}