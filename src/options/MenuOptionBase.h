#include "windows/WindowManager.h"
#include <string>

/// <summary>
/// base class for MenuOption
/// </summary>
class MenuOptionBase
{
	public:
	MenuOptionBase(){};
	virtual ~MenuOptionBase(){};
	virtual void on_select() = 0;
	virtual void on_shift_select() = 0;
	virtual bool open_window() = 0;
	virtual std::string get_display_name() = 0;
	std::string display_name;
	WindowManager* window_manager;
};