#include "HttpRequest.h"
#include "HttpResponse.h"
#include <string>

class IHttpClient
{
	public:
	virtual HttpResponse get(HttpRequest request, std::string url) = 0;
	virtual HttpResponse post(HttpRequest request, std::string url) = 0;	
};
