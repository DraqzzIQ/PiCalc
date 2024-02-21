#pragma once
#include "io/IOController.h"
#include "options/CallbackMenuOption.h"
#include "windows/InputWindow.h"
#include "windows/MenuWindow.h"
#include <functional>

class FileOptionsMenuWindow: public MenuWindow
{
	public:
	FileOptionsMenuWindow(const std::string& dir, const std::string& filename, std::function<void(const std::string)> callback):
		MenuWindow(CountType::CUSTOM)
	{
		options.clear();
		options.push_back(new CallbackMenuOption<std::string>(
			"=:Open",
			filename,
			[this, callback](std::string filename) {
				WindowManager::close_window(false);
				callback(filename);
				delete this;
			},
			'='));
		options.push_back(new CallbackMenuOption<std::string>(
			"DEL:Delete",
			filename,
			[dir, this](std::string filename) {
				WindowManager::close_window(false);
				IOController::delete_file(dir, filename);
				delete this;
			},
			KEY_DEL));
		options.push_back(new CallbackMenuOption<std::string>(
			"+:Rename",
			filename,
			[dir, this](std::string filename) {
				InputWindow::input("Rename:", [filename, dir, this](std::string new_name) {
					WindowManager::close_window(false);
					IOController::rename_file(dir, filename, new_name);
					delete this;
				});
			},
			'+'));
		options.push_back(new CallbackMenuOption<std::string>(
			"\327:Dublicate",
			filename,
			[dir, this](std::string filename) {
				WindowManager::close_window(false);
				IOController::duplicate_file(dir, filename);
				delete this;
			},
			KEY_MULTIPLY));
		create_menu();
	};
};