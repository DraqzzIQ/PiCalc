#pragma once
#ifdef PICO
#include "Window.h"
#include "pico/stdlib.h"

class BatteryWindow: public Window
{
	public:
	BatteryWindow();
	~BatteryWindow();
	Frame updateWindow();
};

#endif