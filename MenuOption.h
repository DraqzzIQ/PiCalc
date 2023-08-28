#pragma once
#include <string>
#include <iostream>
#include "Window.h"
#include "WindowManager.h"
#include "Calculator.h"

/// <summary>
/// base class for all menu options
/// </summary>
class MenuOption
{
	public:
		/// <summary>
		/// creates a new menuOption
		/// </summary>
		/// <param name="display_name">name of that option</param>
		/// <param name="window_manager">window_manager to add windows to</param>
		MenuOption(const std::string display_name, WindowManager* window_manager);
		/// <summary>
		/// can be passed a derived class of Window. On selection of this MenuOption a
		/// new instance of that class will be added to window manager
		/// </summary>
		/// <typeparam name="window_type">derived Class of Window</typeparam>
		template<class window_type>
		void add_window(){ _selected_window = new window_type(); }
		/// <summary>
		/// fired when option is selected
		/// </summary>
		void on_select();
		/// <summary>
		/// gets the display name
		/// </summary>
		/// <returns>display name</returns>
		std::string get_display_name();

	private:
		/// <summary>
		/// name to display in the menu
		/// </summary>
		std::string _display_name;
		/// <summary>
		/// window to open when option is selected
		/// </summary>
		Window* _selected_window;
		/// <summary>
		/// window manager to add window to
		/// </summary>
		WindowManager* _window_manager;
};