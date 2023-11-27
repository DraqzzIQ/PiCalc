#include "WolframAlphaWindow.h"

WolframAlphaWindow::WolframAlphaWindow():
	client(base_url)
{
}

WolframAlphaWindow::~WolframAlphaWindow()
{
}

void WolframAlphaWindow::handle_key_down(KeyPress keypress)
{
	if (keypress.key_calculator == Chars::CHAR_TO_KEYCODE.at("=")) {
		request(text[text.size() - 1]);
		text.push_back("");
		return;
	}

	std::string character = Chars::KEY_MAP[keypress.key_keyboard];

	if (text[text.size() - 1].size() > 15)
		text.push_back(character);
	else {
		text[text.size() - 1] += character;
	}
}

void WolframAlphaWindow::request(std::string query)
{
	Params params = default_params;
	params.emplace("i", query);
	HttpResponse res = client.get(endpoint, HttpRequest(params));

	if (res.error()) {
		text.push_back("error: ");
		for (int i = 0; i < res.error_msg.size(); i += 16) {
			text.push_back(res.error_msg.substr(i, 16));
		}
		return;
	}

	for (int i = 0; i < res.body.size(); i += 16) {
		text.push_back(res.body.substr(i, 16));
	}
}
