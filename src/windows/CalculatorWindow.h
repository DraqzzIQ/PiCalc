#pragma once
#include "calculator/Equation.h"
#include "constant/Graphics.h"
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
	double result;
	Bitset2D result_rendered;
	bool calculated;
	std::vector<double> variables;
};
