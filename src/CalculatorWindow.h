#pragma once
#include "Window.h"
#include "Equation.h"
#include "Graphics.h"
#include <iostream>

class CalculatorWindow : public Window {
	public:
		CalculatorWindow();
		~CalculatorWindow();
		bitset_2d update_window();
		void handle_key_down(KeyPress keypress);
	private:
		Equation* equation;
};