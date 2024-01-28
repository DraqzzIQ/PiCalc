#include "windows/WindowManager.h"
#include <iostream>

class InstanceSelectionWindow: public Window
{
	public:
	InstanceSelectionWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;
	void setup(std::vector<Window*> instances);

	private:
	std::vector<Window*> _instances;
	WindowManager* _window_manager;
	int _current_page = 0;
	void scroll_up();
	void scroll_down();
};
