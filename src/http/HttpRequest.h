#include <string>

struct HttpRequest
{	
	std::string body;

	HttpRequest(std::string& body)
	{
		this->body = body;
	}
};
