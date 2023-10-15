#include "windows/SysInfoWindow.h"

SysInfoWindow::SysInfoWindow()
{
	screen_symbols = DynamicBitset(Graphics::SCREEN_SYMBOLS.size(), true);
}

Bitset2D SysInfoWindow::update_window()
{
	text = std::vector<std::string>(3);

	text[0] = "OS Version: " + OS_VERSION;
	text[1] = "Total Heap: " + std::to_string(Utils::get_total_heap());
	text[2] = "Free Heap: " + std::to_string(Utils::get_free_heap());

	create_menu();
	corner_y = current_page * 4 * line_height;
	return get_render_canvas();
}
