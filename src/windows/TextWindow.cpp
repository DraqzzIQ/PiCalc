#include "windows/TextWindow.h"

TextWindow::~TextWindow() {}

void TextWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_raw == Chars::KEY_MAP.at("up")) scroll_up();
	else if (keypress.key_raw == Chars::KEY_MAP.at("down")) scroll_down();
	else if (keypress.key_raw == Chars::KEY_MAP.at("left")) scroll_left();
	else if (keypress.key_raw == Chars::KEY_MAP.at("right")) scroll_right();
}

Bitset2D TextWindow::update_window()
{
	create_menu();

	corner_y = current_page * 4 * line_height;

	return get_render_canvas();
}

void TextWindow::create_menu()
{
	for (uint32_t i = 0; i < text.size(); i++) {
		add_to_window(Graphics::create_text(text[i], Graphics::SYMBOLS_6_HIGH, text_spacing), 0, 1 + i * line_height);
	}
}

int TextWindow::pages_count() const
{
	return static_cast<int>(ceil(static_cast<double>(text.size()) / 4));
}

void TextWindow::scroll_up()
{
	if (current_page > 0) current_page--;
}

void TextWindow::scroll_down()
{
	if (current_page < pages_count() - 1) current_page++;
}