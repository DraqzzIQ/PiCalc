#include "WindowManager.h"

WindowManager::WindowManager(IRenderer& renderer)
{
	this->renderer = &renderer;
	this->windows = std::vector<IRenderItem>();
}

void WindowManager::add_window(const IRenderItem& window)
{
	this->windows.push_back(window);
}

void WindowManager::remove_window()
{
	this->windows.pop_back();
}

void WindowManager::update()
{
	if (this->windows.size() > 0)
		this->windows.back().update(this->pixels);

	this->renderer->render(this->pixels);
}