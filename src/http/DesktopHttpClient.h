#include "IHttpClient.h"
#include "httplib.h"

class DesktopHttpClient : IHttpClient
{
	public:
	DesktopHttpClient();
	HttpResponse get(HttpRequest req, std::string url);
	HttpResponse post(HttpRequest req, std::string url);
};
