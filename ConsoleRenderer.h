#pragma once
#include "IRenderer.h"
#include "Constants.h"

class ConsoleRenderer : public IRenderer
{
	public:
		ConsoleRenderer();

		void render(const render_plane pixels);

	private:
		void clear_screen();
};

