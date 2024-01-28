#pragma once
#include "Window.h"
#include "datastructs/Decimal.h"
#ifdef PICO
#include "hardware/adc.h"
#include "pico/stdlib.h"
#endif


class BatteryWindow: public Window
{
	public:
	BatteryWindow();
	~BatteryWindow();
	void update_window() override;
};