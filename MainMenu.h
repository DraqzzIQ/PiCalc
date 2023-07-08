#pragma once
#include "Window.h"
#include "MenuOption.h"
#include "Constants.h"
#include "Graphics.h"
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
		/// called when the window gets rerendered
		/// </summary>
		/// <returns>pixels to render</returns>
		render_plane update_window();

	private:
		/// <summary>
		/// container for all options
		/// </summary>
		std::vector<MenuOption*> _options;
};