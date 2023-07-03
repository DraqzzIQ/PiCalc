#pragma once
#include "IRenderer.h"

class ConsoleRenderer : public IRenderer
{
	public:
		ConsoleRenderer();
		virtual ~ConsoleRenderer();

		virtual void render(const bool pixels[32][96]);

	private:
		void clear_screen();
};

