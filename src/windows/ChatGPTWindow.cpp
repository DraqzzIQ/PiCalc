#include "windows/ChatGPTWindow.h"

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

	if (res.error()) {
		add_text("\nerror: " + res.error_msg);
		return;
	}

	_text.handle_key_down('\n');
	add_text(extract_answer(res.body));
}

void ChatGPTWindow::on_return_key()
{
	Threading::get_instance()->enqueue_thread({ [this] { this->request(this->_input); } });
}


std::string ChatGPTWindow::extract_answer(std::string response)
{
	std::smatch match;

	if (std::regex_search(response, match, _response_pattern))
		return (match[1]);
	else
		return ("error: no match\n" + response);
}