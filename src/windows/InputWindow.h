#pragma once
#include "constant/Chars.h"
#include "utils/Utils.h"
#include "windows/Window.h"
#include "windows/WindowManager.h"
#include <functional>

class InputWindow: public Window
{
	public:
	InputWindow(const std::string& prompt, std::function<void(std::string&)> callback);
	~InputWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	static void input(const std::string& prompt, std::function<void(std::string&)> callback);

	private:
	std::string _prompt;
	std::string _input;

	uint32_t _cursor_index = 0;
	uint64_t _blink_timer;
	bool _cursor_on = true;
	void add_cursor(Bitset2D& bitset);

	std::function<void(std::string&)> _callback;
};