#include "WindowManager.h"

WindowManager::WindowManager()
{
	this->windows = std::vector<IRenderer>();
}

void WindowManager::add_window(const IRenderer& window)
{
	this->windows.push_back(window);
}