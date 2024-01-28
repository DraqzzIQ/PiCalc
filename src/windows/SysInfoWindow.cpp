#include "windows/SysInfoWindow.h"

SysInfoWindow::SysInfoWindow()
{
}

void SysInfoWindow::update_window()
{
	_text = std::vector<std::string>(3);

	_text[0] = "OS Version: " + OS_VERSION;
	_text[1] = "Total Heap: " + std::to_string(Utils::get_total_heap());
	_text[2] = "Free Heap: " + std::to_string(Utils::get_free_heap());

	create_menu();
	_frame.corner_y = _current_page * 4 * _line_height;
	_frame.screen_symbols = 0xFFFF;
}
