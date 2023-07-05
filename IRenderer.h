#pragma once

class IRenderer
{
	public:
		virtual ~IRenderer() {};
		virtual void render(const render_plane pixels) = 0;
};

