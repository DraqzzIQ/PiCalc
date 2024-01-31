#pragma once
#include "HttpHeaders.h"

struct HttpResponse {
	Headers headers;
	std::string body;
	int status_code;
	std::string error_msg;

	HttpResponse(Headers headers, std::string body, int status_code)
	{
		this->headers = headers;
		this->body = body;
		this->status_code = status_code;
	}

	HttpResponse(std::string body, int status_code)
	{
		this->body = body;
		this->status_code = status_code;
	}

	HttpResponse(std::string error_msg)
	{
		this->error_msg = error_msg;
	}

	bool error() const
	{
		return this->error_msg != "";
	}
};
