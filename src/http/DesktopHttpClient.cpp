#include "http/DesktopHttpClient.h"
#ifndef PICO

DesktopHttpClient::DesktopHttpClient(std::string base_url):
	IHttpClient(base_url),
	client(base_url)
{
}

HttpResponse DesktopHttpClient::get(std::string path, HttpRequest req)
{
	if (httplib::Result res = client.Get(path, req.params, req.headers))
		return HttpResponse(res->headers, res->body, res->status);
	else
		return HttpResponse(httplib::to_string(res.error()));
}

HttpResponse DesktopHttpClient::post(std::string path, HttpRequest req)
{
	if (httplib::Result res = client.Post(path, req.headers, req.body, "application/json"))
		return HttpResponse(res->headers, res->body, res->status);
	else
		return HttpResponse(httplib::to_string(res.error()));
}

void DesktopHttpClient::set_bearer_auth_token(std::string token)
{
	client.set_bearer_token_auth(token);
}
#endif
