#pragma once
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include <string>

class IHttpClient
{
	public:
	IHttpClient(std::string base_url);
	virtual HttpResponse get(HttpRequest req, std::string path) = 0;
	virtual HttpResponse post(HttpRequest req, std::string path) = 0;
	virtual void set_bearer_auth_token(std::string token) = 0;
	virtual ~IHttpClient(){};

	private:
	std::string base_url;
};
