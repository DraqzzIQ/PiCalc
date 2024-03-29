#pragma once
#include "threading/Threading.h"
#include "windows/ChatWindow.h"
#include <regex>
#ifdef PICO
#include <http/PicoHttpClient.h>
#else
#include <http/DesktopHttpClient.h>
#endif

#ifndef OPENAI_API_KEY
#pragma message("warning: OPENAI_API_KEY not defined")
#define OPENAI_API_KEY "DEMO"
#endif

class ChatGPTWindow: public ChatWindow
{
	public:
	ChatGPTWindow();
	~ChatGPTWindow();

	private:
	void on_return_key() override;
	void request(std::string query);
	std::string extract_answer(std::string);
	const std::string _base_url = "api.openai.com";
	const std::string _endpoint = "/v1/chat/completions";
	const std::string _model = "gpt-4-1106-preview";
	const std::string _body1 = R"({
	"model": ")" + _model + R"(",
	"messages": [{"role": "user", "content": ")";
	const std::string _body2 = R"("}],
	"temperature": 0.6
})";
	const std::string _openai_api_key = OPENAI_API_KEY;
	const Headers _default_headers{
		{ "Content-Type", "application/json" },
		{ "Authorization", "Bearer " + _openai_api_key }
	};
	const std::regex _response_pattern = std::regex(R"x("content":\s*"([^"]*)",?\s*\},)x");
#ifdef PICO
	PicoHttpClient _client;
#else
	DesktopHttpClient _client;
#endif
};
