#include "windows/WindowManager.h"

WindowManager* WindowManager::_instance = nullptr;

WindowManager* WindowManager::get_instance()
{
	if (!_instance)
		_instance = new WindowManager();

	return _instance;
}

WindowManager::WindowManager()
{
}

void WindowManager::add_window(Window* window)
{
	_windows.push(window);
}

void WindowManager::minimize_window()
{
	if (!_windows.empty()) {
		Window* top = _windows.top();
		_windows.pop();
		if (_window_instances.count(&typeid(*top)) == 0) _window_instances[&typeid(*top)] = std::vector<Window*>(1, top);
		else if (std::find(_window_instances[&typeid(*top)].begin(), _window_instances[&typeid(*top)].end(), top) == _window_instances[&typeid(*top)].end()) // if instance not already in vector
			_window_instances[&typeid(*top)].push_back(top);
	}
}

void WindowManager::close_window(bool dispose)
{
	if (!_windows.empty()) {
		Window* top = _windows.top();
		_windows.pop();
		if (dispose)
			delete top;
	}
}

void WindowManager::update(bool force_rerender)
{
	for (size_t i = 0; i < IRenderer::Renderers.size(); i++) {
		if (!_windows.empty()) IRenderer::Renderers.at(i)->render(_windows.top()->update_window(), _windows.top()->screen_symbols, force_rerender);
		else IRenderer::Renderers.at(i)->render(Graphics::LOGO_SCREEN, DynamicBitset(Graphics::SCREEN_SYMBOLS.size(), true), force_rerender);
	}
}

void WindowManager::handle_key_down(KeyPress keypress)
{
	if (keypress.shift && keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("AC")) {
#ifdef PICO
		gpio_put(28, 0);
#endif
	} else if (keypress.alpha && keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("DEL")) {
		if (_windows.size() > 0) minimize_window();
	} else if (keypress.shift && keypress.key_raw == Chars::CHAR_TO_KEYCODE.at("DEL")) {
		if (_windows.size() > 1) close_window();
	} else if (_windows.size() > 0) _windows.top()->handle_key_down(keypress);
}

void WindowManager::handle_key_up(KeyPress keypress)
{
	if (_windows.size() > 0) _windows.top()->handle_key_up(keypress);
}
