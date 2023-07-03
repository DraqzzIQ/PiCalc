#pragma once

#include "IRenderItem.h"
#include "IRenderer.h"

#include <vector>

class WindowManager
{
	public:
		WindowManager(IRenderer& renderer);

		void add_window(const IRenderItem& window);
		void remove_window();

	private:
		IRenderer* renderer;
		std::vector<IRenderItem> windows;
		bool pixels[32][96];

		void update();
};

