#pragma once
#include "HttpHeaders.h"
#include "http/HttpParams.h"
#include <string>

struct HttpRequest {
	Params params;
	Headers headers;
	std::string body;

	HttpRequest(Params params, Headers headers, std::string body)
	{
		this->params = params;
		this->headers = headers;
		this->body = body;
	}

	HttpRequest(Headers headers, std::string body)
	{
		this->headers = headers;
		this->body = body;
	}

	HttpRequest(Params params, Headers headers)
	{
		this->params = params;
		this->headers = headers;
	}

	HttpRequest(Params params)
	{
		this->params = params;
	}

	HttpRequest(Headers headersy)
	{
		this->headers = headers;
	}

	HttpRequest()
	{
	}
};
