#pragma once
#include "MenuOptionBase.h"

class TextMenuOption: public MenuOptionBase
{
	public:
	TextMenuOption(const std::string& name)
	{
		display_name = name;
	}
};