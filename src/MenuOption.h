#pragma once
#include <string>
#include <iostream>
#include "Window.h"
#include "WindowManager.h"
#include "InstanceSelectionWindow.h"

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
		/// <summary>
		/// fired when option is selected
		/// </summary>
		virtual void on_select();
		/// <summary>
		/// opens a window of type T if there is only one instance of it,
		/// otherwise opens an InstanceSelectionWindow
		/// returns true if a window was opened else false
		/// </summary>
		template <typename T>
		bool open_window()
		{
 			if(!window_manager->has_window<T>())
				return false;

			std::vector<Window*> instances = window_manager->get_windows<T>();
			if(instances.size() == 1)
				window_manager->add_window(instances[0]);
			else
			{
				InstanceSelectionWindow* instance_selection_window;
				if(window_manager->has_window<InstanceSelectionWindow>())
					instance_selection_window = dynamic_cast<InstanceSelectionWindow*>(window_manager->get_windows<InstanceSelectionWindow>()[0]);
				else
					instance_selection_window = new InstanceSelectionWindow(window_manager);

				instance_selection_window->setup(instances);
				window_manager->add_window(instance_selection_window);
			}
			return true;
		}
		/// <summary>
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