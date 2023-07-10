#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer()
{
}

void ConsoleRenderer::render(const render_plane pixels)
{
	set_cursor_top_left();

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

	int fps = calculate_fps();

	std::cout << out << std::endl << "fps: " << fps << "     " << std::endl;
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

int ConsoleRenderer::calculate_fps()
{
	clock_t delta_ticks = clock() - current_ticks;
	int rounded_fps = static_cast<int>(std::round((CLOCKS_PER_SEC / (double)delta_ticks)));
	current_ticks = clock();

	return rounded_fps;
}

void ConsoleRenderer::set_cursor_top_left()
{
	std::cout << "\x1B[H";
}