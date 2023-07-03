#include "ConsoleRenderer.h"
#include <iostream>

ConsoleRenderer::ConsoleRenderer()
{
}

ConsoleRenderer::~ConsoleRenderer()
{
}

void ConsoleRenderer::render(const bool pixels[32][96])
{
	clear_screen();

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 96; j++)
		{
			if (pixels[i][j]) std::cout << '\xFE';
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void ConsoleRenderer::clear_screen()
{
	std::cout << "\x1B[2J\x1B[H";
}