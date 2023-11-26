#pragma once
#include "windows/Window.h"

class WolframAlphaWindow: public Window
{
	public:
	WolframAlphaWindow();
	~WolframAlphaWindow();

	Bitset2D update_window();
};