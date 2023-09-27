#include "InstanceSelectionWindow.h"

InstanceSelectionWindow::InstanceSelectionWindow(WindowManager* window_manager)
{
    _window_manager = window_manager;
}

render_plane InstanceSelectionWindow::update_window()
{
    corner_y = _current_page * 32;

	return get_render_canvas();
}

void InstanceSelectionWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == Chars::KEY_MAP.at("up")) scroll_up();
	else if (keypress.key_raw == Chars::KEY_MAP.at("down")) scroll_down();
	else if (keypress.key_raw < 10 && keypress.key_raw < _instances.size())
    {
        _window_manager->minimize_window();
        _window_manager->add_window(_instances[keypress.key_raw]);
    }
}

void InstanceSelectionWindow::setup(std::vector<Window*> instances)
{
    window.clear();
    for (size_t i = 0; i < instances.size(); i++)
    {
        add_to_window(instances[i]->window, 0, i * 32);
        add_to_window(Graphics::create_text(std::to_string(i)), 91, i * 32 + 22);
    }
    _instances = instances;
}

void InstanceSelectionWindow::scroll_up()
{
	if(_current_page > 0)
		_current_page--;
}

void InstanceSelectionWindow::scroll_down()
{
	if(_current_page < _instances.size() - 1)
		_current_page++;
}