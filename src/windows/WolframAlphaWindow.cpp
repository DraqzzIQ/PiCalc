#include "WolframAlphaWindow.h"

WolframAlphaWindow::WolframAlphaWindow()
{
	std::string base_url = "https://api.wolframalpha.com/v1/result";
	std::string app_id = "";
#ifdef PICO
	PicoHttpClient client = PicoHttpClient(base_url);
#else
	DesktopHttpClient client = DesktopHttpClient(base_url);
#endif

	Params params{
		{ "appid", app_id },
		{ "i", "How far is Los Angeles from New York?" },
		{ "units", "metric" }
	};

	HttpResponse res = client.get("/", HttpRequest(params));

	if (res.error()) {
		for (int i = 0; i < res.error_msg.size(); i += 16) {
			text.push_back(res.error_msg.substr(i, 16));
		}
		return;
	}

	for (int i = 0; i < res.body.size(); i += 16) {
		text.push_back(res.body.substr(i, 16));
	}

	text.push_back("status code: " + res.status_code);
}

WolframAlphaWindow::~WolframAlphaWindow()
{
}
