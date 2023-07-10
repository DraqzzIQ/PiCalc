#pragma once
#include "Window.h"
#include "MenuOption.h"
#include "Constants.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "WindowManager.h"
#include <vector>
#include <format>

/// <summary>
/// provides a menu for the user to select from
/// </summary>
class MainMenu : public Window
{
	public:
		MainMenu();
		MainMenu(const std::vector<MenuOption*>& options);

		/// <summary>
		/// deletes an option
		/// </summary>
		/// <param name="name">name of option to delete</param>
		/// <returns>success status</returns>
		bool delete_option(const std::string name);
		/// <summary>
		/// adds an option
		/// </summary>
		/// <param name="option">option to add</param>
		/// <param name="index">index where to insert</param>
		void add_option(MenuOption* option, const int index);
		/// <summary>
		/// gets an option by name
		/// </summary>
		/// <param name="name">name of option to get</param>
		/// <returns>option</returns>
		MenuOption* get_option(const std::string name);
		/// <summary>
		/// returns the number of options
		/// </summary>
		const size_t options_size();
		/// <summary>
		/// called when the window gets rerendered
		/// </summary>
		/// <returns>pixels to render</returns>
		render_plane update_window();
		/// <summary>
		/// handles keyboard events
		/// </summary>
		void handle_keyboard_event(int key);

	private:
		/// <summary>
		/// container for all options
		/// </summary>
		std::vector<MenuOption*> _options;
		const int _max_options = 10;
		/// <summary>
		/// max number of options per page
		/// </summary>
		const int _options_per_page = 4;
		/// <summary>
		/// index of currently selected page
		/// </summary>
		int _current_page = 0;
		/// <summary>
		/// height of an option line
		/// </summary>
		const int _line_height = 8;
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
};