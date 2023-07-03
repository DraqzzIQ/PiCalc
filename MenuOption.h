#pragma once
#include <string>

struct MenuOption
{
	public:
		std::string display_name;

		MenuOption(const std::string display_name);
		MenuOption();
};