#ifndef PICO
#include "DesktopHttpClient.h"

DesktopHttpClient::DesktopHttpClient(std::string& baseUrl):
	IHttpClient(baseUrl),
	client(baseUrl)
{
}

HttpResponse DesktopHttpClient::get(HttpRequest& req, std::string& path)
{
	httplib::Result res = client.Get(path, req.headers);
	return HttpResponse(res->headers, res->body, res->status);
}

HttpResponse DesktopHttpClient::post(HttpRequest& req, std::string& path)
{
	httplib::Result res = client.Post(path, req.headers, req.body, "application/json");
	return HttpResponse(res->headers, res->body, res->status);
}

void DesktopHttpClient::set_bearer_auth_token(std::string& token)
{
	client.set_bearer_token_auth(token);
}
#endif