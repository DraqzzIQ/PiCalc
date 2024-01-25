#include "BatteryWindow.h"

BatteryWindow::BatteryWindow():
	Window()
{
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_IN);
	gpio_pull_down(pin);
}