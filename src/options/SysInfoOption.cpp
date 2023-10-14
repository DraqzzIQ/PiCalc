#include "SysInfoOption.h"

void SysInfoOption::on_select()
{
	if (!open_window<SysInfoWindow>()) window_manager->add_window(new SysInfoWindow());
}

void SysInfoOption::on_shift_select()
{
	window_manager->add_window(new SysInfoWindow());
}