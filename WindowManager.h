#pragma once
#include "Window.h"
#include "IRenderer.h"
#include "Graphics.h"
#include "KeyPress.h"
#include <stack>
#include <vector>

/// <summary>
/// provides functionality for managing, rendering and keyboard events for windows
/// </summary>
class WindowManager
{
	public:
		WindowManager(std::vector<IRenderer*>* renderers);

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
		void update(bool force_rerender = false);
		/// <summary>
		/// handles keydown events
		/// </summary>
		/// <param name="key">key that got pressed</param>
		void handle_key_down(KeyPress keypress);
		/// <summary>
		/// handles keyup events
		/// </summary>
		/// <param name="key">key that got released</param>
		void handle_key_up(KeyPress keypress);

	private:
		/// <summary>
		/// the renderer used
		/// </summary>
		std::vector<IRenderer*>* _renderers;
		/// <summary>
		/// the window stack
		/// </summary>
		std::stack<Window*> _windows;
};

