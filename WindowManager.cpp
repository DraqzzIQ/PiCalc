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
	if(!_windows.empty())
	delete _windows.top();
	_windows.pop();
}

void WindowManager::update()
{
	if (_windows.size() > 0)
		_renderer->render(_windows.top()->update_window(), _windows.top()->screen_symbols);
	else
		_renderer->render(Graphics::LOGO_SCREEN, std::vector<bool>(Graphics::SCREEN_SYMBOLS.size(), true));
}

void WindowManager::handle_key_down(KeyPress keypress) {
	if(keypress.alpha && keypress.key == KEY_MAP.at("ac")){
		pop_window();
	}
	if (_windows.size() > 0)
		_windows.top()->handle_key_down(keypress);
}

void WindowManager::handle_key_up(KeyPress keypress) {
	if (_windows.size() > 0)
		_windows.top()->handle_key_up(keypress);
}