#pragma once

#include "Constants.h"
#include <vector>

class Graphics
{
	public:
		Graphics();
		~Graphics();

		static const render_plane EMPTY_SCREEN = render_plane(SCREEN_HEIGHT, std::vector<bool>(SCREEN_WIDTH, false));
};

