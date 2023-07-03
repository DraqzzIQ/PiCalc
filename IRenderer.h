#pragma once

class IRenderer
{
	public:
		virtual ~IRenderer() {};
		virtual void render(const bool pixels[32][96]) = 0;
};

