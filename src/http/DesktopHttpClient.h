#pragma once
#ifndef PICO
#include "http/IHttpClient.h"
#include <httplib.h>

class DesktopHttpClient: public IHttpClient
{
	public:
	DesktopHttpClient(std::string _base_url);
	HttpResponse get(std::string path, HttpRequest req) override;
	HttpResponse post(std::string path, HttpRequest req) override;
	void set_bearer_auth_token(std::string token) override;

	private:
	httplib::Client _client;
};
#endif