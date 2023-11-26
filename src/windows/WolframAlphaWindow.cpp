#include "WolframAlphaWindow.h"

WolframAlphaWindow::WolframAlphaWindow()
{
#ifdef PICO
	PicoHttpClient client = PicoHttpClient("https://google.com");
#else
	DesktopHttpClient client = DesktopHttpClient("https://google.com");
#endif

	HttpResponse res = client.get(HttpRequest(), "/");

	for (int i = 0; i < res.body.size(); i += 16) {
		text.push_back(res.body.substr(i, 16));
	}

	text.push_back("status code: " + res.status_code);
}

WolframAlphaWindow::~WolframAlphaWindow()
{
}
