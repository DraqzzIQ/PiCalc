#pragma once
#include "HttpHeaders.h"
#include <string>

struct HttpRequest {
	Headers headers;
	std::string body;

	HttpRequest(Headers headers, std::string body)
	{
		this->headers = headers;
		this->body = body;
	}
};
