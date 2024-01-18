#include "windows/InstanceSelectionWindow.h"

InstanceSelectionWindow::InstanceSelectionWindow()
{
	_window_manager = WindowManager::get_instance();
}

Frame InstanceSelectionWindow::update_window()
{
	_corner_y = _current_page * 32;

	return Frame(get_render_canvas(), _screen_symbols);
}

bool InstanceSelectionWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("up")) scroll_up();
	else if (keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("down")) scroll_down();
	else if (keypress.key_raw < 10 && keypress.key_raw < _instances.size()) {
		_window_manager->minimize_window();
		_window_manager->add_window(_instances[keypress.key_raw]);
	} else return false;

	return true;
}

void InstanceSelectionWindow::setup(std::vector<Window*> instances)
{
	_window.clear();
	for (uint32_t i = 0; i < instances.size(); i++) {
		add_to_window(instances[i]->get_preview(), 0, i * 32);
		add_to_window(Graphics::create_text(std::to_string(i)), 91, i * 32 + 22);
	}
	_instances = instances;
}

void InstanceSelectionWindow::scroll_up()
{
	if (_current_page > 0) _current_page--;
}

void InstanceSelectionWindow::scroll_down()
{
	if (_current_page < _instances.size() - 1) _current_page++;
}
