#pragma once
#include "windows/TextWindow.h"
#ifdef PICO
#include <http/PicoHttpClient.h>
#else
#include <http/DesktopHttpClient.h>
#endif

class WolframAlphaWindow: public TextWindow
{
	public:
	WolframAlphaWindow();
	~WolframAlphaWindow();
	void handle_key_down(KeyPress keypress);
	private:
	HttpResponse request(std::string query);
	const std::string base_url = "https://api.wolframalpha.com";
	const std::string endpoint = "/v1/result";
	const std::string app_id = "";
	const Params default_params{
                { "appid", app_id },
                { "units", "metric" }
        };
#ifdef PICO
	PicoHttpClient client;
#else
	DesktopHttpClient client;
#endif
};
