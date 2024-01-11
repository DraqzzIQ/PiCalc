#pragma once
#ifndef PICO
#include "http/IHttpClient.h"
#include <httplib.h>

class DesktopHttpClient: public IHttpClient
{
	public:
	DesktopHttpClient(std::string _base_url);
	HttpResponse get(std::string path, HttpRequest req);
	HttpResponse post(std::string path, HttpRequest req);
	void set_bearer_auth_token(std::string token);

	private:
	httplib::Client _client;
};
#endif