#pragma once
#include "options/MenuOption.h"
#include "windows/SettingsWindow.h"

class SettingsOption: public MenuOption
{
	public:
	SettingsOption(WindowManager* window_manager): MenuOption("Settings", window_manager) {}
	void on_select();
	void on_shift_select();
};