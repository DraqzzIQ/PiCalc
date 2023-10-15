#pragma once
#include "calculator\Equation.h"
#include "constant\Graphics.h"
#include "windows/Window.h"
#include <iostream>

class CalculatorWindow: public Window
{
	public:
	CalculatorWindow();
	~CalculatorWindow();
	Bitset2D update_window();
	void handle_key_down(KeyPress keypress);

	private:
	Equation* equation;
	std::vector<double> variables;
};
