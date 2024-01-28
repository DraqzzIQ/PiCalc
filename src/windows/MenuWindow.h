#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "options/MenuOptionBase.h"
#include "windows/Window.h"
#include "windows/WindowManager.h"
#include <cmath>
#include <vector>

/// <summary>
/// provides a menu for the user to select from
/// </summary>
class MenuWindow: public Window
{
	public:
	MenuWindow(FONT& font, bool count = true);
	MenuWindow(bool count = true);
	~MenuWindow();
	/// <summary>
	/// handles key presses
	/// </summary>
	bool handle_key_down(KeyPress keypress) override;
	/// <summary>
	/// creates the menu out of the text
	/// </summary>
	void create_menu();
	/// <summary>
	/// scrolls the text up
	/// </summary>
	void scroll_up();
	/// <summary>
	/// scrolls the text down
	/// </summary>
	void scroll_down();
	/// <summary>
	/// container for all text lines
	/// </summary>
	std::vector<MenuOptionBase*> options;

	private:
	/// <summary>
	/// font to be used
	/// </summary>
	FONT& _font;
	/// <summary>
	/// height of each line
	/// </summary>
	uint8_t _line_height;
	/// <summary>
	/// lines per page
	/// </summary>
	uint8_t _lines_per_page;
	/// <summary>
	/// current page
	/// </summary>
	uint8_t _page = 0;
	/// <summary>
	/// whether to count the lines
	/// </summary>
	bool _count;
};