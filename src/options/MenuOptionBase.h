#pragma once
#include "windows/WindowManager.h"
#include <string>

/// <summary>
/// base class for MenuOption
/// </summary>
class MenuOptionBase
{
	public:
	virtual void on_select(){};
	virtual void on_shift_select(){};
	std::string display_name;
};