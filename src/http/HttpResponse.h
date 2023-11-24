#pragma once
#include "HttpHeaders.h"

struct HttpResponse {
	Headers headers;
	std::string body;
	int status_code;

	HttpResponse(Headers& headers, std::string& body, int status_code)
	{
		this->headers = headers;
		this->body = body;
		this->status_code = status_code;
	}
};