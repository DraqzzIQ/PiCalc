#include "WindowManager.h"

WindowManager::WindowManager(std::vector<IRenderer*> *renderers)
{
	_renderers = renderers;
}

void WindowManager::add_window(Window *window)
{
	_windows.push(window);
}

void WindowManager::pop_window()
{
	if (!_windows.empty())
		delete _windows.top();
	_windows.pop();
}

void WindowManager::update(bool force_rerender)
{
	for (size_t i = 0; i < _renderers->size(); i++)
	{
		if (!_windows.empty())
			_renderers->at(i)->render(_windows.top()->update_window(), _windows.top()->screen_symbols, force_rerender);
		else
			_renderers->at(i)->render(Graphics::LOGO_SCREEN, std::vector<bool>(Graphics::SCREEN_SYMBOLS.size(), true), force_rerender);
	}
}

void WindowManager::handle_key_down(KeyPress keypress)
{
	if (keypress.alpha && keypress.key_raw == Chars::KEY_MAP.at("AC"))
	{
		pop_window();
	}
	if (_windows.size() > 0)
		_windows.top()->handle_key_down(keypress);
}

void WindowManager::handle_key_up(KeyPress keypress)
{
	if (_windows.size() > 0)
		_windows.top()->handle_key_up(keypress);
}