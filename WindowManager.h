#pragma once
#include "Window.h"
#include "IRenderer.h"
#include "Graphics.h"
#include <stack>

/// <summary>
/// provides functionality for managing, rendering and keyboard events for windows
/// </summary>
class WindowManager
{
	public:
		WindowManager(IRenderer* renderer);

		/// <summary>
		/// adds a window to the window stack
		/// </summary>
		void add_window(Window* window);
		/// <summary>
		/// removes the top window from the window stack
		/// </summary>
		void pop_window();
		/// <summary>
		/// rerenders the top window
		/// </summary>
		void update();

	private:
		/// <summary>
		/// the renderer used
		/// </summary>
		IRenderer* renderer;
		/// <summary>
		/// the window stack
		/// </summary>
		std::stack<Window*> windows;
};

