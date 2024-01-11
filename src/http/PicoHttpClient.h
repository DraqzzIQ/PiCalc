#pragma once
#ifdef PICO
#include "http/IHttpClient.h"

class PicoHttpClient: public IHttpClient
{
	public:
	PicoHttpClient(std::string _base_url);
	HttpResponse get(std::string path, HttpRequest req);
	HttpResponse post(std::string path, HttpRequest req);
	void set_bearer_auth_token(std::string token);

	private:
};
#endif