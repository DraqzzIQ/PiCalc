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
		add_text("\nerror: " + res.error_msg);
		return;
	}

	_text.handle_key_down('\n');
	add_text(extract_answer(res.body));
}

void ChatGPTWindow::on_return_key()
{
	Threading::get_instance()->enqueue_thread({ std::bind(&ChatGPTWindow::request, this, _input) });
}


std::string ChatGPTWindow::extract_answer(std::string response)
{
	std::smatch match;

	if (std::regex_search(response, match, _response_pattern))
		return (match[1]);
	else
		return ("error: no match\n" + response);
}