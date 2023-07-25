#pragma once
#include "Window.h"
#include "Equation.h"
#include "Graphics.h"
#include "Keyboard.h"

class Calculator : public Window {
	public:
		Calculator();

		render_plane update_window();
		void handle_key_down(uint8_t key);
	private:
		Equation equation;
};

