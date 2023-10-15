#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "options/MenuOption.h"
#include "windows/Window.h"
#include "windows/WindowManager.h"
#include <cmath>
#include <vector>

/// <summary>
/// provides a menu for the user to select from
/// </summary>
class MenuWindow: public Window
{
	public:
	MenuWindow(WindowManager* window_manager);
	~MenuWindow();
	/// <summary>
	/// called when the window gets rerendered
	/// </summary>
	/// <returns>pixels to render</returns>
	Bitset2D update_window();
	/// <summary>
	/// handles keydown events
	/// </summary>
	/// <param name="key">key that got pressed</param>
	void handle_key_down(KeyPress keypress);
	/// <summary>
	/// window manager to add windows to
	/// </summary>
	WindowManager* window_manager;
	/// <summary>
	/// container for all options
	/// </summary>
	std::vector<MenuOption*> options;
	/// <summary>
	/// max number of options per page
	/// </summary>
	const int options_per_page = 4;
	/// <summary>
	/// index of currently selected page
	/// </summary>
	int current_page = 0;
	/// <summary>
	/// height of an option line
	/// </summary>
	const int line_height = 8;
	/// <summary>
	/// creates the menu out of the options
	/// </summary>
	void create_menu();
	/// <summary>
	/// number of pages
	/// </summary>
	const int pages_count();
	/// <summary>
	/// scrolls the menu up
	/// </summary>
	void scroll_up();
	/// <summary>
	/// scrolls the menu down
	/// </summary>
	void scroll_down();

	private:
};
