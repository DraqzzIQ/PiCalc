#pragma once
#include "utils/Utils.h"
#include "windows/NotesWindow.h"

class ChatWindow: public TextWindow
{
	public:
	ChatWindow();
	~ChatWindow();
	bool handle_key_down_special(KeyPress keypress) override;

	void add_text(std::string text);

	protected:
	virtual void on_return_key();
};
