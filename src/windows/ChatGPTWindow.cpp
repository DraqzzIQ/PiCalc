#include "windows/ChatGPTWindow.h"
#ifdef PICO
#include <http/PicoHttpClient.h>
#else
#include <http/DesktopHttpClient.h>
#endif

ChatGPTWindow::ChatGPTWindow():
	_client(_base_url)
{
}

ChatGPTWindow::~ChatGPTWindow()
{
}

void ChatGPTWindow::request(std::string query)
{
	HttpResponse res = _client.post(_endpoint, HttpRequest(_default_headers, _body1 + _input + _body2));

	std::cout << _body1 + _input + _body2 << std::endl;

	if (res.error()) {
		add_text("error: " + res.error_msg, true, true, false);
		_text.push_back("");
		return;
	}
	std::cout << std::endl
			  << std::endl
			  << res.body << std::endl;

	add_text(extract_answer(res.body), true, true, false);
	_text.push_back("");
}

void ChatGPTWindow::on_return_key()
{
	request(_input);
}


std::string ChatGPTWindow::extract_answer(std::string response)
{
	std::smatch match;

	if (std::regex_search(response, match, _response_pattern))
		return (match[1]);
	else
		return ("error: no match\n" + response);
}