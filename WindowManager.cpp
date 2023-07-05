#include "WindowManager.h"

WindowManager::WindowManager(IRenderer& renderer)
{
	this->renderer = &renderer;
}

void WindowManager::add_window(const Window& window)
{
	windows.push_back(window);
}

void WindowManager::pop_window()
{
	windows.pop_back();
}

void WindowManager::update()
{
	if (windows.size() > 0)
		renderer->render(windows.back().update_window());
	else
		renderer->render(Graphics::EMPTY_SCREEN);
}