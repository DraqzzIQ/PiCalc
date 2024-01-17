#pragma once
#include "utils/Utils.h"
#include "windows/Window.h"
#include "windows/WindowManager.h"
#include <functional>

class InputWindow: public Window
{
	public:
	InputWindow(
		std::string promt,
		std::function<void(std::string)> callback);
	~InputWindow();
	Bitset2D update_window();
	bool handle_key_down(KeyPress keypress);

	static void input(std::string prompt, std::function<void(std::string)> callback);

	private:
	std::string _prompt;
	std::string _input;

	Bitset2D _rendered;

	uint32_t _cursor_index = 0;
	uint64_t _blink_timer;
	bool _cursor_on = true;
	Bitset2D add_cursor(Bitset2D bitset);

	std::function<void(std::string)> _callback;
};