#pragma once
#include "io/IOController.h"
#include "options/CallbackMenuOption.h"
#include "windows/InputWindow.h"
#include "windows/MenuWindow.h"
#include <functional>

class FileOptionsMenu: public MenuWindow
{
	public:
	FileOptionsMenu(const std::string& dir, const std::string& filename, std::function<void(const std::string)> callback):
		MenuWindow(CountType::CUSTOM)
	{
		options.clear();
		options.push_back(new CallbackMenuOption<std::string>("=:Open", filename, callback, '='));
		options.push_back(new CallbackMenuOption<std::string>(
			"DEL:Delete",
			filename,
			[dir](std::string filename) { IOController::delete_file(dir, filename); },
			KEY_DEL));
		options.push_back(new CallbackMenuOption<std::string>(
			"+:Rename",
			filename,
			[dir](std::string filename) {
				InputWindow::input("Rename:", [filename, dir](std::string new_name) {
					IOController::rename_file(dir, filename, new_name);
				});
			},
			'+'));
		options.push_back(new CallbackMenuOption<std::string>(
			"\327:Dublicate",
			filename,
			[dir](std::string filename) { IOController::duplicate_file(dir, filename); },
			KEY_MULTIPLY));
		create_menu();
	};
};