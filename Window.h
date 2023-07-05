#pragma once

#include <vector>
#include "Constants.h"

class Window
{
	public:
		Window();
		virtual ~Window() {};
		virtual render_plane update_window() = 0;

		render_plane pixels;
		int corner_x;
		int corner_y;

		render_plane get_render_window();
};

