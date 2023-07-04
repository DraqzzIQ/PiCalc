#pragma once

class IRenderer
{
	public:
		virtual ~IRenderer() {};
		virtual void render(const bool pixels[SCREEN_HEIGHT][SCREEN_WIDTH]) = 0;
};

