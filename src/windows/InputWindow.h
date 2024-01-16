#pragma once
#include "windows/Window.h"
#include "windows/WindowManager.h"

class InputWindow: public Window
{
	public:
	InputWindow();
	~InputWindow();
	Bitset2D update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	void set_prompt(std::string prompt);
	std::string get_input();

	private:
	std::string _prompt;
	std::string _input;

	uint32_t _cursor_index = 0;
};