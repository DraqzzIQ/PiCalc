#include "WindowManager.h"

WindowManager::WindowManager(IRenderer* renderer)
{
	_renderer = renderer;
}

void WindowManager::add_window(Window* window)
{
	_windows.push(window);
}

void WindowManager::pop_window()
{
	_windows.pop();
}

void WindowManager::update()
{
	if (_windows.size() > 0)
		_renderer->render(_windows.top()->update_window(), _windows.top()->screen_symbols);
	else
		_renderer->render(Graphics::LOGO_SCREEN, std::vector<bool>(Graphics::ScreenSymbols.size(), false));
}

void WindowManager::handle_key_down(uint8_t key) {
	if (_windows.size() > 0)
		_windows.top()->handle_key_down(key);
}

void WindowManager::handle_key_up(uint8_t key) {
	if (_windows.size() > 0)
		_windows.top()->handle_key_up(key);
}