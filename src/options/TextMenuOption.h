#pragma once
#include "MenuOptionBase.h"

class TextMenuOption: public MenuOptionBase
{
	public:
	TextMenuOption(const std::string& name)
	{
		select_key = 0;
		display_name = name;
	}
};