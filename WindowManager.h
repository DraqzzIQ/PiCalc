#pragma once

#include "IRenderer.h"

#include <vector>

class WindowManager
{
	public:
		WindowManager();

		void add_window(const IRenderer& window);

	private:
		std::vector<IRenderer> windows;
};

