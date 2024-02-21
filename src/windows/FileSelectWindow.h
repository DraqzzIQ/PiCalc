#pragma once
#include "MenuWindow.h"
#include "io/IOController.h"
#include "options/CallbackMenuOption.h"
#include "windows/FileOptionsMenu.h"
#include "windows/WindowManager.h"
#include <functional>

class FileSelectWindow: public MenuWindow
{
	public:
	FileSelectWindow(const std::string& dir, std::function<void(std::string&)> callback):
		MenuWindow()
	{
		std::vector<std::string> files = IOController::list_dir(dir);
		options.clear();
		for (int i = 0; i < files.size(); i++) {
			options.push_back(new CallbackMenuOption<std::string>(files[i], files[i], [this, callback, dir](std::string filename) {
				WindowManager::add_window(new FileOptionsMenu(dir, filename, [this, callback](std::string filename) {
					WindowManager::close_window(false);
					callback(filename);
					delete this;
				}));
			}));
		}
		create_menu();
	}

	static void select_file(const std::string& dir, std::function<void(std::string&)> callback)
	{
		WindowManager::add_window(new FileSelectWindow(dir, callback));
	}
};
