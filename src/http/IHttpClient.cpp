#include "http/IHttpClient.h"

IHttpClient::IHttpClient(std::string baseUrl)
{
	this->baseUrl = baseUrl;
}