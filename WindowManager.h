#pragma once

#include "Window.h"
#include "IRenderer.h"

#include <vector>

class WindowManager
{
	public:
		WindowManager(IRenderer& renderer);

		void add_window(const Window& window);
		void pop_window();

	private:
		IRenderer* renderer;
		std::vector<Window> windows;
		bool pixels[SCREEN_HEIGHT][SCREEN_WIDTH];

		void update();
};

