#include "constant/Chars.h"
#include "windows/WindowManager.h"
#include <iostream>

class InstanceSelectionWindow: public Window
{
	public:
	bool handle_key_down(KeyPress keypress) override;
	void setup(const std::vector<Window*>& instances);

	private:
	std::vector<Window*> _instances;
	WindowManager* _window_manager;
	uint8_t _current_page = 0;
	void scroll_up();
	void scroll_down();
	void render();
};
