#include "HttpRequest.h"
#include "HttpResponse.h"
#include <string>

class IHttpClient
{
	public:
	virtual HttpResponse get(HttpRequest req, std::string url) = 0;
	virtual HttpResponse post(HttpRequest req, std::string url) = 0;	
};
