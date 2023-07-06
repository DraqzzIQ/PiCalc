#pragma once

#include "Window.h"
#include "IRenderer.h"
#include "Graphics.h"

#include <stack>

class WindowManager
{
	public:
		WindowManager(IRenderer* renderer);

		void add_window(Window* window);
		void pop_window();
		void update();

	private:
		IRenderer* renderer;
		std::stack<Window*> windows;
};

