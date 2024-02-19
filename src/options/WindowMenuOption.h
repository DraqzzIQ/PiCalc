#pragma once
#include "options/MenuOptionBase.h"
#include "windows/InstanceSelectionWindow.h"
#include "windows/Window.h"

/// <summary>
/// base class for all menu options
/// </summary>
template <typename T>
class WindowMenuOption: public MenuOptionBase
{
	public:
	/// <summary>
	/// creates a new WindowMenuOption
	/// </summary>
	/// <param name="display_name">name of that option</param>
	/// <param name="window_manager">window_manager to add windows to</param>
	WindowMenuOption(const std::string& name)
	{
		display_name = name;
	}
	/// <summary>
	/// called when option is selected
	/// </summary>
	void on_select() override
	{
		if (!open_window()) _window_manager->add_window(new T());
	}
	/// <summary>
	/// called when option is selected with shift active
	/// </summary>
	void on_shift_select() override
	{
		_window_manager->add_window(new T());
	}
	/// <summary>
	/// opens a window of type T if there is only one instance of it,
	/// otherwise opens an InstanceSelectionWindow
	/// returns true if a window was opened else false
	/// </summary>
	bool open_window()
	{
		if (!_window_manager->has_window<T>()) return false;

		std::vector<Window*> instances = _window_manager->get_windows<T>();
		if (instances.size() == 1) _window_manager->add_window(instances[0]);
		else {
			InstanceSelectionWindow* instance_selection_window;
			if (_window_manager->has_window<InstanceSelectionWindow>()) instance_selection_window = dynamic_cast<InstanceSelectionWindow*>(_window_manager->get_windows<InstanceSelectionWindow>()[0]);
			else instance_selection_window = new InstanceSelectionWindow();

			instance_selection_window->setup(instances);
			_window_manager->add_window(instance_selection_window);
		}
		return true;
	}

	private:
	WindowManager* _window_manager;
};
