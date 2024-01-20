#include "renderers/ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer()
{
#ifdef _WIN32
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 1600, 605, TRUE);

	// Windows exe fix
	DWORD consoleMode;
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleMode(outputHandle, &consoleMode)) {
		SetConsoleMode(outputHandle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
#endif
}

void ConsoleRenderer::render(const Frame& frame, bool force_rerender)
{
	if (!force_rerender && already_rendered(frame)) return;

	set_cursor_top_left();

	std::string out = "";

	out += get_display_border();
	out += "\n# ";

	for (uint32_t i = 0; i < frame.screen_symbols.size(); i++) {
		if (frame.screen_symbols[i]) {
			out += Graphics::SCREEN_SYMBOLS[i];
		} else {
			out += std::string(Graphics::SCREEN_SYMBOLS[i].length(), ' ');
		}
		out += "  ";
	}

	out += std::string(113, ' ');
	out += "#\n";

	for (uint32_t i = 0; i < SCREEN_HEIGHT; i++) {
		out += "# ";
		for (uint32_t j = 0; j < SCREEN_WIDTH; j++) {
			if (frame.pixels.get_bit(j, i)) out += '\xFE';
			else out += " ";
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

	for (size_t i = 0; i < (SCREEN_WIDTH + 1) * 2 + 1; i++) { border += '#'; }
	return border;
}

void ConsoleRenderer::set_cursor_top_left()
{
	std::cout << "\x1B[H";
}
