#pragma once
#include "constant/Graphics.h"
#include "renderers/IRenderer.h"
#include "keyboard/KeyPress.h"
#include "windows/Window.h"
#include <stack>
#include <typeinfo>
#include <unordered_map>
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
	/// if 1 window instance is already open
	/// it's pushed to the top of the window stack
	/// if > 1 window instances are already open
	/// opens an instance selection window
	/// </summary>
	template <typename T> std::vector<Window*> get_windows()
	{
		return _window_instances[&typeid(T)];
	}
	/// <summary>
	/// returns true if a window instance is already open
	/// else false
	/// </summary>
	template <typename T> bool has_window()
	{
		if (_window_instances.count(&typeid(T)) > 0 && _window_instances[&typeid(T)].size() > 0) return true;
		return false;
	}
	/// <summary>
	/// removes the top window from the window stack
	/// and saves it to the window instances
	/// </summary>
	void minimize_window();
	/// <summary>
	/// removes the top window from the window stack
	/// and deletes it
	/// </summary>
	void close_window();
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
	/// <summary>
	/// stores all window instances in background
	/// </summary>
	std::unordered_map<const std::type_info*, std::vector<Window*>> _window_instances;
};
