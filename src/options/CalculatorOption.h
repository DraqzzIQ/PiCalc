#pragma once
#include "windows/CalculatorWindow.h"
#include "options/MenuOption.h"

class CalculatorOption: public MenuOption
{
	public:
	CalculatorOption(WindowManager* window_manager): MenuOption("Calculator", window_manager) {}
	void on_select();
	void on_shift_select();
};
