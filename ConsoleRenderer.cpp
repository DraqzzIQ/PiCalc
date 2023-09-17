#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer()
{
	#ifdef _WIN32
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 1600, 600, TRUE); // 800 width, 100 height
	#endif
}

void ConsoleRenderer::render(const render_plane& pixels, const dynamic_bitset& screen_symbols, bool force_rerender)
{	
	if(!force_rerender && already_rendered(pixels, screen_symbols))
		return;
		
	set_cursor_top_left();

	std::string out = "";

	out += get_display_border();
	out += "\n# ";

	for (int i = 0; i < screen_symbols.size(); i++) {
		if (screen_symbols[i]) { out += Graphics::SCREEN_SYMBOLS[i]; }
		else { out += std::string(Graphics::SCREEN_SYMBOLS[i].length(), ' '); }
		out += "  ";
	}

	out += std::string(113, ' ');
	out += "#\n";

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

void ConsoleRenderer::set_cursor_top_left()
{
	std::cout << "\x1B[H";
}