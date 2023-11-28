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
		text.push_back("");
		request(input);
		input = "";
		return;
	}

	add_text(Chars::KEY_MAP[keypress.key_calculator], false, false, false)
}

void WolframAlphaWindow::request(std::string query)
{
	Params params = default_params;
	params.emplace("i", query);
	HttpResponse res = client.get(endpoint, HttpRequest(params));

	if (res.error()) {
		add_text("error: " + res.error_msg, true, true, false);
		return;
	}
	
	add_text(res.body, true, true, false);
}
