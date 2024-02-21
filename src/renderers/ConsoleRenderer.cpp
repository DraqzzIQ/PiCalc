#ifndef PICO
#include "Renderer.h "

const std::vector<std::string> Renderer::SCREEN_SYMBOLS = { "S", "A", "M", "STO", "RCL", "STAT", "CMPLX", "MAT", "VCT", "D", "R", "G", "FIX", "SCI", "Math", ">", "<", "Disp" };

void Renderer::init()
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

void Renderer::render(const Frame& frame)
{
	set_cursor_top_left();

	std::string out = "";

	out += get_display_border();
	out += "\n# ";

	for (uint32_t i = 0; i < 15; i++) {
		if (frame.get_screen_symbol(i)) {
			out += SCREEN_SYMBOLS[i];
		} else {
			out += std::string(SCREEN_SYMBOLS[i].length(), ' ');
		}
		out += "  ";
	}

	out += std::string(125, ' ');
	out += "#\n";

	uint32_t x_end = frame.corner_x + SCREEN_WIDTH;
	uint32_t y_end = frame.corner_y + SCREEN_HEIGHT;
	for (uint32_t y = frame.corner_y; y < y_end; y++) {
		out += "# ";
		for (uint32_t x = frame.corner_x; x < x_end; x++) {
			if (x < frame.pixels.width() && y < frame.pixels.height() && frame.pixels.get_bit(x, y)) out += '\xFE';
			else out += " ";
			out += " ";
		}
		out += "#\n";
	}
	out += get_display_border();

	std::cout << out << std::endl;
}

std::string Renderer::get_display_border()
{
	std::string border = "";

	for (size_t i = 0; i < (SCREEN_WIDTH + 1) * 2 + 1; i++) { border += '#'; }
	return border;
}

void Renderer::set_cursor_top_left()
{
	std::cout << "\x1B[H";
}

#endif