#pragma once
#include "windows/Window.h"
#include "windows/WindowManager.h"
#include <functional>
#include "utils/Utils.h"
#include "keyboard/IKeyboard.h"
#ifdef PICO
#include "keyboard/PicoKeyboard.h"
#else
#include "keyboard/SDLKeyboard.h"
#endif

class InputWindow : public Window
{
	public:
	InputWindow();
	~InputWindow();
	Bitset2D update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	std::function<void(std::string)> _finnished_callback;

	void set_prompt(std::string prompt);
	std::string get_input();
	bool _finnished = false;
	bool get_finnished();

	static std::string input(std::string prompt);
	static IKeyboard* keyboard;

	private:
	std::string _prompt;
	std::string _input;

	Bitset2D _rendered;

	uint32_t _cursor_index = 0;
	uint64_t _blink_timer;
	bool _cursor_on = true;
	Bitset2D add_cursor(Bitset2D bitset);
};