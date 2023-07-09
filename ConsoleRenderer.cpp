#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer()
{
}

void ConsoleRenderer::render(const render_plane pixels)
{
	clear_screen();

	std::string out = "";

	out += get_display_border();
	out += '\n';

	for (size_t i = 0; i < SCREEN_HEIGHT; i++)
	{
		out += "# ";
		for (size_t j = 0; j < SCREEN_WIDTH; j++)
		{
			if (pixels[j][i])
				out  += '\xFE';
			else
				out +=  " ";
			out += " ";
		}
		out += "#\n";
	}
	out += get_display_border();

	std::cout << out << std::endl;
}

std::string ConsoleRenderer::get_display_border()
{
	std::string border = "";

	for (size_t i = 0; i < (SCREEN_WIDTH + 1) * 2 + 1; i++)
	{
		border += '#';
	}
	return border;
}

void ConsoleRenderer::clear_screen()
{
	std::cout << "\x1B[H";
}