#pragma once

#include "IWindow.h"
#include "IRenderer.h"

#include <vector>

class WindowManager
{
	public:
		WindowManager(IRenderer& renderer);

		void add_window(const IWindow& window);
		void pop_window();

	private:
		IRenderer* renderer;
		std::vector<IWindow> windows;
		bool pixels[SCREEN_HEIGHT][SCREEN_WIDTH];

		void update();
};

