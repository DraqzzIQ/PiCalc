#pragma once
#include "constant/Chars.h"
#include "constant/Graphics.h"
#include "datastructs/Frame.h"
#include "keyboard/KeyPress.h"
#include "renderers/ConsoleRenderer.h"
#include "utils/Utils.h"
#include "windows/CalculatorWindow.h"
#include "windows/Window.h"
#ifdef PICO
#include "pico/stdlib.h"
#include "renderers/DisplayRenderer.h"
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
	static void init(Window* main_menu_window);
	/// <summary>
	/// adds a window to the window stack
	/// </summary>
	static void add_window(Window* window);
	/// <summary>
	/// if 1 window instance is already open
	/// it's pushed to the top of the window stack
	/// if > 1 window instances are already open
	/// opens an instance selection window
	/// </summary>
	template <typename T>
	static std::vector<Window*> get_windows()
	{
		return _window_instances[&typeid(T)];
	}
	/// <summary>
	/// returns true if a window instance is already open
	/// else false
	/// </summary>
	template <typename T>
	static bool has_window()
	{
		if (_window_instances.count(&typeid(T)) > 0 && _window_instances[&typeid(T)].size() > 0) return true;
		return false;
	}
	/// <summary>
	/// removes the top window from the window stack
	/// and saves it to the window instances
	/// </summary>
	static void minimize_window();
	/// <summary>
	/// removes the top window from the window stack
	/// and deletes it
	/// </summary>
	static void close_window(bool dispose = true);
	/// <summary>
	/// rerenders the top window
	/// </summary>
	static void update(bool force_rerender = false);
	/// <summary>
	/// handles keydown events
	/// </summary>
	/// <param name="key">key that got pressed</param>
	static void handle_key_down(KeyPress keypress);
	/// <summary>
	/// handles keyup events
	/// </summary>
	/// <param name="key">key that got released</param>
	static void handle_key_up(KeyPress keypress);
	/// <summary>
	/// checks if frame to render is the same as currently rendered
	/// </summary>
	/// <param name="frame">frame to check</param>
	/// <returns>true if same else false</returns>
	static bool already_rendered(const Frame& frame);

	private:
#ifdef PICO
	static DisplayRenderer display_renderer;
#endif
	static ConsoleRenderer console_renderer;
	/// <summary>
	/// tracks if shift is pressed
	/// </summary>
	static bool _shift;
	/// <summary>
	/// tracks if alpha is pressed
	/// </summary>
	static bool _alpha;
	/// <summary>
	/// whether PiCalc is locked in the Calculator app to behave exactly like the original
	/// To escape: MODE -> SHIFT -> =
	/// </summary>
	static bool _panic_mode;
	/// <summary>
	/// the Window to be shown in Panic mode
	/// </summary>
	static Window* _panic_window;
	/// <summary>
	/// stores, which key was pressed last
	/// </summary>
	static KEY _last_key;

	static Bitset2D _rendered_pixels;
	static uint16_t _rendered_screen_symbols;
	static uint32_t _rendered_corner_x;
	static uint32_t _rendered_corner_y;

	/// <summary>
	/// the window stack
	/// </summary>
	static std::stack<Window*> _windows;
	/// <summary>
	/// stores all window instances in background
	/// </summary>
	static std::unordered_map<const std::type_info*, std::vector<Window*>> _window_instances;
};
