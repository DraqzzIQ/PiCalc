#pragma once
#ifndef PICO
#include "IHttpClient.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

class DesktopHttpClient: IHttpClient
{
	public:
	DesktopHttpClient(std::string& baseUrl);
	HttpResponse get(HttpRequest& req, std::string& path);
	HttpResponse post(HttpRequest& req, std::string& path);
	void set_bearer_auth_token(std::string& token);

	private:
	httplib::Client client;
};
#endif