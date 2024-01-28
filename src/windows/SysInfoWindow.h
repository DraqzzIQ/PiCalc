#pragma once
#include "utils/Utils.h"
#include "windows/TextWindow.h"

class SysInfoWindow: public TextWindow
{
	public:
	SysInfoWindow();
	void update_window() override;

	private:
};
