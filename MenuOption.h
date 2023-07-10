#pragma once
#include <string>
#include <iostream>
#include "Window.h"
#include "WindowManager.h"

/// <summary>
/// base class for all menu options
/// </summary>
class MenuOption
{
	public:
		MenuOption(const std::string display_name, WindowManager* window_manager, Window* class_name);
		MenuOption(const std::string display_name, WindowManager* window_manager);
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
		Window* _class_name;
		WindowManager* _window_manager;
};