#pragma once
#include "constant/Chars.h"
#include "constant/Graphics.h"
#include "keyboard/KeyPress.h"
#include "renderers/IRenderer.h"
#include "windows/Window.h"
#ifdef PICO
#include "pico/stdlib.h"
#endif
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
	/// <summary>
	/// returns instance of singleton WindowManager
	/// </summary>
	static WindowManager* get_instance();
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
	template <typename T>
	std::vector<Window*> get_windows()
	{
		return _window_instances[&typeid(T)];
	}
	/// <summary>
	/// returns true if a window instance is already open
	/// else false
	/// </summary>
	template <typename T>
	bool has_window()
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
	void close_window(bool dispose = true);
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
	/// private constructor to prevent instantiation
	/// </summary>
	WindowManager();
	/// <summary>
	/// private deconstructor to prevent deletion
	/// </summary>
	~WindowManager();
	/// <summary>
	/// private copy constructor and assignmnt operator to prevent copying
	/// </summary>
	WindowManager(const WindowManager&);
	WindowManager& operator=(const WindowManager&);
	/// <summary>
	/// tracks if shift is pressed
	/// </summary>
	bool _shift = false;
	/// <summary>
	/// tracks if alpha is pressed
	/// </summary>
	bool _alpha = false;
	/// <summary>
	/// the instance
	/// </summary>
	static WindowManager* _instance;
	/// <summary>
	/// the window stack
	/// </summary>
	std::stack<Window*> _windows;
	/// <summary>
	/// stores all window instances in background
	/// </summary>
	std::unordered_map<const std::type_info*, std::vector<Window*>> _window_instances;
};
