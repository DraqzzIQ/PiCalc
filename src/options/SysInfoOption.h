#pragma once
#include "MenuOption.h"
#include "SysInfoWindow.h"

class SysInfoOption: public MenuOption
{
	public:
	SysInfoOption(WindowManager* window_manager): MenuOption("System Info", window_manager) {}
	void on_select();
	void on_shift_select();
};