#include "SettingsOption.h"

void SettingsOption::on_select()
{
    if(!open_window<SettingsWindow>())
        window_manager->add_window(new SettingsWindow(window_manager));
}

void SettingsOption::on_shift_select()
{
    window_manager->add_window(new SettingsWindow(window_manager));
}