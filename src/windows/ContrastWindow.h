#pragma once
#include "constant/Chars.h"
#include "windows/Window.h"
#ifdef PICO
#include "utils/I2CUtils.h"
#endif

class ContrastWindow: public Window
{
	public:
	ContrastWindow();
	bool handle_key_down(KeyPress keypress) override;

	private:
	void render();
	uint8_t get_contrast();
	void set_contrast(uint8_t contrast);
};