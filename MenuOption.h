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
		MenuOption(const std::string display_name, WindowManager* window_manager);

		/// <summary>
		/// can be passed a derived class of Window. On selection of this MenuOption a
		/// new instance of that class will be added to window manager
		/// </summary>
		/// <typeparam name="window_name">derived Class of Window</typeparam>
		template<class window_name>
		void add_window() {_window_name = new window_name();};
		//MenuOption(const std::string display_name, WindowManager* window_manager);
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
		Window* _window_name;
		WindowManager* _window_manager;
};