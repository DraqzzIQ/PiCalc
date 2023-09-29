#include "WindowManager.h"
#include <iostream>

class InstanceSelectionWindow : public Window
{
    public:
        InstanceSelectionWindow(WindowManager* window_manager);
        Bitset2D update_window();
        void handle_key_down(KeyPress keypress);
        void setup(std::vector<Window*> instances);
    private:
        std::vector<Window*> _instances;
        WindowManager* _window_manager;
        int _current_page = 0;
        void scroll_up();
        void scroll_down();
};