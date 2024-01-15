#include "PongWindow.h"

PongWindow::PongWindow()
{
	_menu = Menu::GAME;
	_settings = 0b1000;
}

PongWindow::~PongWindow() {}

Bitset2D PongWindow::update_window()
{
	return Bitset2D();
}

bool PongWindow::handle_key_down(KeyPress keypress)
{
	return true;
}