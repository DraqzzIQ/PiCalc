#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer()
{
}

void ConsoleRenderer::render(const render_plane pixels)
{
	clear_screen();

	std::string out = "";

	for (size_t i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (size_t j = 0; j < SCREEN_WIDTH; j++)
		{
			if (!pixels[j][i])
				out  += '\xFE';
			else
				out +=  " ";
			out += " ";
		}
		out += '\n';
	}

	std::cout << out;
}

void ConsoleRenderer::clear_screen()
{
	std::cout << "\x1B[2J\x1B[H";
}