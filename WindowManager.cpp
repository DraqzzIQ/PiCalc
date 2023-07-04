#include "WindowManager.h"

WindowManager::WindowManager(IRenderer& renderer)
{
	this->renderer = &renderer;
}

void WindowManager::add_window(const IWindow& window)
{
	this->windows.push_back(window);
}

void WindowManager::pop_window()
{
	this->windows.pop_back();
}

void WindowManager::update()
{
	if (this->windows.size() > 0)
		this->windows.back().update(this->pixels);

	this->renderer->render(this->pixels);
}