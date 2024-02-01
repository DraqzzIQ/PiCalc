#include "windows/ChatWindow.h"

ChatWindow::ChatWindow()
{
}

ChatWindow::~ChatWindow()
{
}

bool ChatWindow::handle_key_down_special(KeyPress keypress)
{
	if (keypress.key_raw == KEY_EQUAL) {
		add_text("...");
		on_return_key();
		_input = "";
		return true;
	}
	return false;
}

void ChatWindow::add_text(std::string text)
{
	for (uint8_t c : text) _text.handle_key_down(c);
}

void ChatWindow::on_return_key()
{
}