#include "SysInfoOption.h"

void SysInfoOption::on_select()
{
    window_manager->add_window(new SysInfoWindow());
}

void SysInfoOption::on_shift_select()
{
    if(window_manager->has_window<SysInfoWindow>())
        window_manager->open_window<SysInfoWindow>();
    else
        window_manager->add_window(new SysInfoWindow());
}