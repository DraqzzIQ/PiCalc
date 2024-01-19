#include "PongWindow.h"

PongWindow::PongWindow()
{
	_menu = Menu::GAME;
	_settings = 0b1000;
}

PongWindow::~PongWindow() {}

Frame PongWindow::update_window()
{
	return Frame();
}

bool PongWindow::handle_key_down(KeyPress keypress)
{
	return true;
}