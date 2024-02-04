#pragma once
#include "threading/Threading.h"
#include "windows/ChatWindow.h"
#ifdef PICO
#include <http/PicoHttpClient.h>
#else
#include <http/DesktopHttpClient.h>
#endif

#ifndef WOLFRAMALPHA_APPID
#pragma message("warning: WOLFRAMALPHA_APPID not defined")
#define WOLFRAMALPHA_APPID "DEMO"
#endif

class WolframAlphaWindow: public ChatWindow
{
	public:
	WolframAlphaWindow();
	~WolframAlphaWindow();

	private:
	void on_return_key() override;
	void request(std::string query);
	const std::string _base_url = "api.wolframalpha.com";
	const std::string _endpoint = "/v1/result";
	const std::string _app_id = WOLFRAMALPHA_APPID;
	const Params _default_params{
		{ "appid", _app_id },
		{ "units", "metric" }
	};
#ifdef PICO
	PicoHttpClient _client;
#else
	DesktopHttpClient _client;
#endif
};