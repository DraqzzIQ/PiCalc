#include "CalculatorOption.h"

void CalculatorOption::on_select()
{
    window_manager->add_window(new CalculatorWindow());
}

void CalculatorOption::on_shift_select()
{
    if(window_manager->has_window<CalculatorWindow>())
        window_manager->open_window<CalculatorWindow>();
    else
        window_manager->add_window(new CalculatorWindow());
}