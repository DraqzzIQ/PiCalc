#include "WolframAlphaWindow.h"

WolframAlphaWindow::WolframAlphaWindow():
	_client(_base_url)
{
}

WolframAlphaWindow::~WolframAlphaWindow()
{
}

void WolframAlphaWindow::request(std::string query)
{
	Params params = _default_params;
	params.emplace("i", query);
	HttpResponse res = _client.get(_endpoint, HttpRequest(params));

	if (res.error()) {
		add_text("error: " + res.error_msg, true, true, false);
		_text.push_back("");
		return;
	}

	add_text(res.body, true, true, false);
	_text.push_back("");
}

void WolframAlphaWindow::on_return_key()
{
	Threading::get_instance()->enqueue_thread({ std::bind(&WolframAlphaWindow::request, this, _input) });
}