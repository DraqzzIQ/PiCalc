#pragma once

#include <vector>
#include "Constants.h"

class Window
{
	public:
		virtual ~Window() {};
		virtual void update(bool (&pixels)[SCREEN_HEIGHT][SCREEN_WIDTH]) = 0;

	private:
		std::vector<std::vector<bool>> pixels;
		int corner_x;
		int corner_y;

		std::vector<std::vector<bool>> get_render_window();
};

