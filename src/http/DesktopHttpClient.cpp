#ifndef PICO
#include "DesktopHttpClient.h"

DesktopHttpClient::DesktopHttpClient(std::string baseUrl):
	IHttpClient(baseUrl),
	client(baseUrl)
{
	//client.set_ca_cert_path("../ca-bundle.crt");
	auto res = get(HttpRequest(Headers(), ""), "/");
	std::cout << res.body << std::endl;
	std::cout << res.status_code << std::endl;
}

HttpResponse DesktopHttpClient::get(HttpRequest req, std::string path)
{
	httplib::Result res = client.Get(path, req.headers);
	//std::cout << httplib::to_string(res.error()) << std::endl;
        return HttpResponse(res->headers, res->body, res->status);
}

HttpResponse DesktopHttpClient::post(HttpRequest req, std::string path)
{
	httplib::Result res = client.Post(path, req.headers, req.body, "application/json");
	return HttpResponse(res->headers, res->body, res->status);
}

void DesktopHttpClient::set_bearer_auth_token(std::string token)
{
	client.set_bearer_token_auth(token);
}
#endif
