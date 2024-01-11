#include "http/PicoHttpClient.h"
#ifdef PICO

PicoHttpClient::PicoHttpClient(std::string _base_url):
	IHttpClient(_base_url)
{
}

HttpResponse PicoHttpClient::get(std::string path, HttpRequest req)
{
	HttpResponse res = HttpResponse("PicoHttpClient::get() not implemented");
	return res;
}

HttpResponse PicoHttpClient::post(std::string path, HttpRequest req)
{
	HttpResponse res = HttpResponse("PicoHttpClient::post() not implemented");
	return res;
}

void PicoHttpClient::set_bearer_auth_token(std::string token)
{
}

#endif