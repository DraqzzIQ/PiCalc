#include "windows/WindowManager.h"

WindowManager* WindowManager::_instance = nullptr;

WindowManager* WindowManager::get_instance()
{
	if (!_instance) {
		_instance = new WindowManager();
		_instance->add_window(new MainMenuWindow());
		_instance->_panic_window = new CalculatorWindow(true);
		_instance->add_window(_instance->_panic_window);
	}
	return _instance;
}

WindowManager::WindowManager()
{
}

void WindowManager::add_window(Window* window)
{
	if (!_panic_mode) _windows.push(window);
}

void WindowManager::minimize_window()
{
	if (_windows.size() > 1) {
		Window* top = _windows.top();
		_windows.pop();
		if (_window_instances.count(&typeid(*top)) == 0) _window_instances[&typeid(*top)] = std::vector<Window*>(1, top);
		else if (std::find(_window_instances[&typeid(*top)].begin(), _window_instances[&typeid(*top)].end(), top) == _window_instances[&typeid(*top)].end()) // if instance not already in vector
			_window_instances[&typeid(*top)].push_back(top);
	}
}

void WindowManager::close_window(bool dispose)
{
	if (_windows.size() > 1) {
		Window* top = _windows.top();
		_windows.pop();
		if (dispose)
			delete top;
	}
}

void WindowManager::update(bool force_rerender)
{
	for (size_t i = 0; i < IRenderer::Renderers.size(); i++) {
		Frame& frame = _windows.top()->update_and_get_frame();
		frame.set_screen_symbol(0, _shift);
		frame.set_screen_symbol(1, _alpha);
		IRenderer::Renderers.at(i)->render(frame, force_rerender);
	}
}

void WindowManager::handle_key_down(KeyPress keypress)
{
	_shift = keypress.shift;
	_alpha = keypress.alpha;
	if (keypress.shift && keypress.key_raw == KEY_AC && !Utils::charging) {
#ifdef PICO
		// TODO: renove check for charging in new design
		IRenderer::Renderers.at(i)->render(Frame(_panic_mode ? Graphics::ORIGINAL_LOGO : Graphics::PICALC_LOGO, 0xFFFF)
		gpio_put(28, 0);
#endif
	} else if (!_panic_mode && keypress.alpha && keypress.key_raw == KEY_DEL) minimize_window();
	else if (!_panic_mode && keypress.shift && keypress.key_raw == KEY_DEL) close_window();
	else if (_windows.size() > 0) _windows.top()->handle_key_down(keypress);
	switch (_last_key) {
	case 0:
		if (keypress.key_raw == KEY_MODE) _last_key = keypress.key_raw;
		break;
	case KEY_MODE:
		if (keypress.key_raw == KEY_ABS) _last_key = keypress.key_raw;
		else _last_key = 0;
		break;
	case KEY_ABS:
		if (keypress.key_raw == KEY_LOGN) {
			_panic_mode = false;
			_windows.pop();
		}
		_last_key = 0;
	}
}

void WindowManager::handle_key_up(KeyPress keypress)
{
	_shift = keypress.shift;
	_alpha = keypress.alpha;
	if (_windows.size() > 0) _windows.top()->handle_key_up(keypress);
}
