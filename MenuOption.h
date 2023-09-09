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
		/// <summary>
		/// creates a new menuOption
		/// </summary>
		/// <param name="display_name">name of that option</param>
		/// <param name="window_manager">window_manager to add windows to</param>
		MenuOption(const std::string display_name, WindowManager* window_manager);
		virtual ~MenuOption() {};
		// /// <summary>
		/// fired when option is selected
		/// </summary>
		virtual void on_select();
		// /// <summary>
		/// fired when option is selected with shift active
		/// </summary>
		virtual void on_shift_select();
		/// <summary>
		/// gets the display name
		/// </summary>
		/// <returns>display name</returns>
		std::string get_display_name();
		/// <summary>
		/// name to display in the menu
		/// </summary>
		std::string display_name;
		/// <summary>
		/// window manager to add window to
		/// </summary>
		WindowManager* window_manager;
	private:
};