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
		_renderer->render(_windows.top()->update_window());
	else
		_renderer->render(Graphics::LOGO_SCREEN);
}

void WindowManager::handle_keyboard_event(int key)
{
	if (_windows.size() > 0)
		_windows.top()->handle_keyboard_event(key);
}