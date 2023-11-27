#include "WolframAlphaWindow.h"

WolframAlphaWindow::WolframAlphaWindow()
:client(base_url)
{
	HttpResponse res = request("27=x³");

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

WolframAlphaWindow::~WolframAlphaWindow()
{
}

void WolframAlphaWindow::handle_key_down(KeyPress keypress)
{
	std::string character = ;

	if(text.length() < 1 || text[text.length() - 1].size() < 16)
		text += character;
	else
	{
		text.push_back(character);
	}
}

HttpResponse WolframAlphaWindow::request(std::string query)
{
	Params params = default_params;
	params.emplace("i", query);
	return client.get(endpoint, HttpRequest(params));
}
