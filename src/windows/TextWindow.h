#pragma once
#include "Window.h"
#include "datastructs/Equation.h"


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
	Equation _text;
};
