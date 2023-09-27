#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(WindowManager* window_manager) : MenuWindow(window_manager)
{
    options = std::vector<MenuOption*>(3);
    options[0] = new MenuOption("Bluetooth", window_manager);
    options[1] = new MenuOption("Wifi", window_manager);
    options[2] = new SysInfoOption(window_manager);
}