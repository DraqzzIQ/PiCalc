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
	void update_window() override
	{
		clear_window();

		// battery voltage
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 31, 54, 51, 59, 40, 46, 44, 84, 80 }, false);

		_window.set(82, 1, Graphics::SYMBOLS_6_HIGH.at(31), false);
		uint16_t voltage_change = Utils::voltage / 1000;
		_window.set(76, 1, Graphics::SYMBOLS_6_HIGH.at(voltage_change % 10), false);
		voltage_change /= 10;
		_window.set(70, 1, Graphics::SYMBOLS_6_HIGH.at(voltage_change % 10), false);
		voltage_change /= 10;
		_window.set(64, 1, Graphics::SYMBOLS_6_HIGH.at(82), false);
		_window.set(58, 1, Graphics::SYMBOLS_6_HIGH.at(voltage_change % 10), false);

		// charging
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 12, 47, 40, 57, 46, 48, 53, 46, 84, 80 }, false);
		if (Utils::charging) _window.put_chars(58, 9, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 29, 57, 60, 44 }, false);
		else _window.put_chars(58, 9, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 15, 40, 51, 58, 44 }, false);
	}
};