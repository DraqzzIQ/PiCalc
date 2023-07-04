#pragma once
#include "IRenderer.h"
#include "Constants.h"

class ConsoleRenderer : public IRenderer
{
	public:
		ConsoleRenderer();
		virtual ~ConsoleRenderer();

		virtual void render(const bool pixels[SCREEN_HEIGHT][SCREEN_WIDTH]);

	private:
		void clear_screen();
};

