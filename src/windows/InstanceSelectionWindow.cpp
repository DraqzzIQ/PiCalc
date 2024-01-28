#include "windows/InstanceSelectionWindow.h"

InstanceSelectionWindow::InstanceSelectionWindow()
{
	_window_manager = WindowManager::get_instance();
}

void InstanceSelectionWindow::update_window()
{
	_frame.corner_y = _current_page * 32;
}

bool InstanceSelectionWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == 167) scroll_up();
	else if (keypress.key_raw == 168) scroll_down();
	else if (keypress.key_raw < 10 && keypress.key_raw < _instances.size()) {
		_window_manager->minimize_window();
		_window_manager->add_window(_instances[keypress.key_raw]);
	} else return false;

	return true;
}

void InstanceSelectionWindow::setup(std::vector<Window*> instances)
{
	_window.clear();
	for (uint16_t i = 0; i < instances.size(); i++) {
		_window.set(0, i * 32, instances[i]->get_preview(), true);
		_window.put_number_aligned_right(91, i * 32 + 22, Graphics::SYMBOLS_6_HIGH, i);
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
