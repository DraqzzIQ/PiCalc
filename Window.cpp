#include "Window.h"

Window::Window()
{
	corner_x = 0;
	corner_y = 0;
	pixels = render_plane(SCREEN_HEIGHT, std::vector<bool>(SCREEN_WIDTH, false));
}

render_plane Window::get_render_window()
{
	render_plane render_plane;

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		std::vector<bool> row;

		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			row.push_back(pixels[corner_y +i][corner_x + j]);
		}

		render_plane.push_back(row);
	}

	return render_plane;
}