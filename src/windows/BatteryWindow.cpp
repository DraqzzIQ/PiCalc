#include "BatteryWindow.h"

BatteryWindow::BatteryWindow()
{
	_timer = 0;
	_voltage = Decimal(4201365, -6);
#ifdef PICO
	adc_init();
	adc_gpio_init(26);
	adc_select_input(0);

	gpio_init(27);
	gpio_set_dir(27, GPIO_IN);
#endif
}

BatteryWindow::~BatteryWindow()
{
}

void BatteryWindow::update_window()
{
	clear_window();

	// battery voltage
	_window.put_chars(0, 0, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 31, 54, 51, 59, 40, 46, 44, 84, 80 }, false);
#ifdef PICO
	Decimal voltage = Decimal(1149902, -9) * adc_read();
#endif
	KEY_SET voltage_keyset = _voltage.to_key_set(5);
	voltage_keyset.push_back(31);
	_window.put_chars(58, 0, Graphics::SYMBOLS_6_HIGH, voltage_keyset, false);

	// charging
	_window.put_chars(0, 8, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 12, 47, 40, 57, 46, 48, 53, 46, 84, 80 }, false);
#ifdef PICO
	if (gpio_get(27)) _window.put_chars(58, 8, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 29, 57, 60, 44 }, false);
	else _window.put_chars(58, 8, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 15, 40, 51, 58, 44 }, false);
#else
	_window.put_chars(58, 8, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 15, 40, 51, 58, 44 }, false);
#endif
}

void BatteryWindow::update()
{
}