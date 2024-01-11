#pragma once
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include <string>

class IHttpClient
{
	public:
	IHttpClient(std::string _base_url);
	virtual HttpResponse get(std::string path, HttpRequest req) = 0;
	virtual HttpResponse post(std::string path, HttpRequest req) = 0;
	virtual void set_bearer_auth_token(std::string token) = 0;
	virtual ~IHttpClient(){};

	private:
	std::string _base_url;
};
