struct HttpResponse
{
	int status_code;

	HttpResponse(int status_code)
	{
		this->status_code = status_code;
	}
};
