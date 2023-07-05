#pragma once

#include "Constants.h"

class IRenderer
{
	public:
		virtual ~IRenderer() {};
		virtual void render(const render_plane pixels) = 0;
};

