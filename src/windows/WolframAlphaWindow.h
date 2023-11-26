#pragma once
#include "windows/TextWindow.h"
#ifdef PICO
#include <http/PicoHttpClient.h>
#else
#include <http/DesktopHttpClient.h>
#endif

class WolframAlphaWindow: public TextWindow
{
	public:
	WolframAlphaWindow();
	~WolframAlphaWindow();
};