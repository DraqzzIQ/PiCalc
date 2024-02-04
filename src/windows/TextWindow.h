#pragma once
#include "datastructs/Equation.h"
#include "windows/Window.h"


class TextWindow: public Window
{
	public:
	TextWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;
	bool handle_key_up(KeyPress keypress) override;

	protected:
	virtual bool handle_key_down_special(KeyPress keypress);
	bool _calculator_keyboard = false;
	uint8_t i = 0;
	Equation _text;
};
