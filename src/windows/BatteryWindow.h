#pragma once
#include "Window.h"
#include "utils/Utils.h"


class BatteryWindow: public Window
{
	public:
	void update_window() override
	{
		clear_window();

		// battery voltage
		_window.put_chars(0, 1, Graphics::SYMBOLS_6_HIGH, "Voltage: ", false);

		_window.set(82, 1, Graphics::SYMBOLS_6_HIGH.at('V'), false);
		uint16_t voltage_change = Utils::voltage / 1000;
		_window.set(76, 1, Graphics::SYMBOLS_6_HIGH.at((voltage_change % 10) + 48), false);
		voltage_change /= 10;
		_window.set(70, 1, Graphics::SYMBOLS_6_HIGH.at((voltage_change % 10) + 48), false);
		voltage_change /= 10;
		_window.set(64, 1, Graphics::SYMBOLS_6_HIGH.at(','), false);
		_window.set(58, 1, Graphics::SYMBOLS_6_HIGH.at((voltage_change % 10) + 48), false);

		// charging
		_window.put_chars(0, 9, Graphics::SYMBOLS_6_HIGH, "Charging: ", false);
		if (Utils::charging) _window.put_chars(58, 9, Graphics::SYMBOLS_6_HIGH, "True", false);
		else _window.put_chars(58, 9, Graphics::SYMBOLS_6_HIGH, "False", false);
	}
};