#pragma once
#include "constant/Chars.h"
#include "utils/Utils.h"
#include "windows/Window.h"
#include "windows/WindowManager.h"
#include <functional>

class InputWindow: public Window
{
	public:
	InputWindow(const std::string& prompt, std::function<void(std::string&)> callback, bool allow_empty = false);
	~InputWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;
	/// <summary>
	/// get input from the user
	/// </summary>
	/// <param name="prompt">text to show above the input, max. 2 lines</param>
	/// <param name="callback">function to be called after enter is hit</param>
	static void input(const std::string& prompt, std::function<void(std::string&)> callback, bool allow_empty = false);

	private:
	std::string _prompt;
	std::string _input;


	bool _allow_empty;
	uint32_t _cursor_index = 0;
	uint64_t _blink_timer;
	bool _cursor_on = true;
	void add_cursor(Bitset2D& bitset);

	std::function<void(std::string&)> _callback;
};