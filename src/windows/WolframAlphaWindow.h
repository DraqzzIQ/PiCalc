#pragma once
#include "windows/TextWindow.h"
#ifdef PICO
#include <http/PicoHttpClient.h>
#else
#include <http/DesktopHttpClient.h>
#endif

#ifndef WOLFRAMALPHA_APPID
#define WOLFRAMALPHA_APPID "DEMO"
#endif

class WolframAlphaWindow: public TextWindow
{
	public:
	WolframAlphaWindow();
	~WolframAlphaWindow();
	Bitset2D update_window();
	void create_menu();
	bool handle_key_down(KeyPress keypress);

	private:
	void request(std::string query);
	const std::string _base_url = "https://api.wolframalpha.com";
	const std::string _endpoint = "/v1/result";
	const std::string _app_id = WOLFRAMALPHA_APPID;
	const Params _default_params{
		{ "appid", _app_id },
		{ "units", "metric" }
	};
	std::string _input;
	uint64_t _last_blink_time = 0;
	bool _show_cursor = false;
#ifdef PICO
	PicoHttpClient _client;
#else
	DesktopHttpClient _client;
#endif
};
