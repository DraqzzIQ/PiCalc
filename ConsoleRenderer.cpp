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

	std::string out = "";

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 96; j++)
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