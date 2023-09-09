#include "SettingsOption.h"

void SettingsOption::on_select()
{
    window_manager->add_window(new SettingsWindow(window_manager));
}

void SettingsOption::on_shift_select()
{
    if(window_manager->has_window<SettingsWindow>())
        window_manager->open_window<SettingsWindow>();
    else
        window_manager->add_window(new SettingsWindow(window_manager));
}