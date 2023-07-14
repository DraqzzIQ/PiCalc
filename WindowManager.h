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
		/// <summary>
		/// handles keydown events
		/// </summary>
		/// <param name="key">key that got pressed</param>
		void handle_key_down(int key);
		/// <summary>
		/// handles keyup events
		/// </summary>
		/// <param name="key">key that got released</param>
		void handle_key_up(int key);

	private:
		/// <summary>
		/// the renderer used
		/// </summary>
		IRenderer* _renderer;
		/// <summary>
		/// the window stack
		/// </summary>
		std::stack<Window*> _windows;
};

