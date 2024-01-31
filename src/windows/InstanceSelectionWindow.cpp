#include "windows/InstanceSelectionWindow.h"

InstanceSelectionWindow::InstanceSelectionWindow()
{
	_window_manager = WindowManager::get_instance();
}

bool InstanceSelectionWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == 3) scroll_up();
	else if (keypress.key_raw == 4) scroll_down();
	else if (keypress.key_raw - 48 < 10 && keypress.key_raw - 48 < _instances.size()) {
		_window_manager->minimize_window();
		_window_manager->add_window(_instances[keypress.key_raw - 48]);
	} else return false;

	return true;
}

void InstanceSelectionWindow::setup(const std::vector<Window*>& instances)
{
	_instances = instances;
	render();
}

void InstanceSelectionWindow::scroll_up()
{
	if (_current_page > 0) _current_page--;
	render();
}

void InstanceSelectionWindow::scroll_down()
{
	if (_current_page < _instances.size() - 1) _current_page++;
	render();
}

void InstanceSelectionWindow::render()
{
	Window* window = _instances[_current_page];
	window->copy_frame(_frame);
	_window = window->get_window();
	_window.put_number_aligned_right(SCREEN_WIDTH - 1, 0, Graphics::SYMBOLS_6_HIGH, _current_page + 1);
}