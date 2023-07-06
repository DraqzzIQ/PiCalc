#include "WindowManager.h"

WindowManager::WindowManager(IRenderer* renderer)
{
	this->renderer = renderer;
}

void WindowManager::add_window(Window* window)
{
	windows.push(window);
}

void WindowManager::pop_window()
{
	windows.pop();
}

void WindowManager::update()
{
	if (windows.size() > 0)
		renderer->render(windows.top()->update_window());
	else
		renderer->render(Graphics::LOGO_SCREEN);
}