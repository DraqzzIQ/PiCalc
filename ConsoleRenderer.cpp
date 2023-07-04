#include "ConsoleRenderer.h"
#include <iostream>

ConsoleRenderer::ConsoleRenderer()
{
}

ConsoleRenderer::~ConsoleRenderer()
{
}

void ConsoleRenderer::render(const bool pixels[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	clear_screen();

	std::string out = "";

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			if (!pixels[i][j]) out  += '\xFE';
			out +=  " ";
		}
		out += '\n';
	}

	std::cout << out;
}

void ConsoleRenderer::clear_screen()
{
	std::cout << "\x1B[2J\x1B[H";
}