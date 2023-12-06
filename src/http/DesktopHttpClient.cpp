#include "http/DesktopHttpClient.h"
#ifndef PICO

DesktopHttpClient::DesktopHttpClient(std::string _base_url):
	IHttpClient(_base_url),
	_client(_base_url)
{
	_client.set_connection_timeout(1, 0); // 1 second
	_client.set_read_timeout(30, 0); // 30 seconds
	_client.set_write_timeout(30, 0); // 30 seconds
}

HttpResponse DesktopHttpClient::get(std::string path, HttpRequest req)
{
	if (httplib::Result res = _client.Get(path, req.params, req.headers))
		return HttpResponse(res->headers, res->body, res->status);
	else
		return HttpResponse(httplib::to_string(res.error()));
}

HttpResponse DesktopHttpClient::post(std::string path, HttpRequest req)
{
	if (httplib::Result res = _client.Post(path, req.headers, req.body, "application/json"))
		return HttpResponse(res->headers, res->body, res->status);
	else
		return HttpResponse(httplib::to_string(res.error()));
}

void DesktopHttpClient::set_bearer_auth_token(std::string token)
{
	_client.set_bearer_token_auth(token);
}
#endif
