#pragma once
#include "MenuWindow.h"
#include "io/IOController.h"
#include "options/CallbackMenuOption.h"
#include "windows/WindowManager.h"
#include <functional>

class FileSelectWindow: public MenuWindow
{
	public:
	FileSelectWindow(const std::string& dir, std::function<void(std::string&)> callback):
		MenuWindow(true)
	{
		_callback = callback;
		std::vector<std::string> files = IOController::list_dir(dir);
		options.clear();
		for (int i = 0; i < files.size(); i++) {
			options.push_back(new CallbackMenuOption<std::string>(files[i], files[i], [this](std::string filename) {
				WindowManager::get_instance()->close_window(false);
				_callback(filename);
				delete this;
			}));
		}
		create_menu();
	}

	static void select_file(const std::string& dir, std::function<void(std::string&)> callback)
	{
		WindowManager::get_instance()->add_window(new FileSelectWindow(dir, callback));
	}

	private:
	std::function<void(std::string&)> _callback;
};
