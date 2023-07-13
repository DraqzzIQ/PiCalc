#pragma once
#include "Constants.h"

/// <summary>
/// provides an interface for renderers
/// </summary>
class IRenderer
{
	public:
		virtual ~IRenderer() {};
		/// <summary>
		/// renders the given pixels
		/// </summary>
		/// <param name="pixels">pixels to render</param>
		virtual void render(const render_plane pixels, const std::vector<bool> screenSymbols) = 0;
};

