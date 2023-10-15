#include "options/CalculatorOption.h"

void CalculatorOption::on_select()
{
	if (!open_window<CalculatorWindow>()) window_manager->add_window(new CalculatorWindow());
}

void CalculatorOption::on_shift_select()
{
	window_manager->add_window(new CalculatorWindow());
}
