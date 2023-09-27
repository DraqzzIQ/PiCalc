#pragma once
#include "Constants.h"
#include "Graphics.h"
#include <stddef.h>

/// <summary>
/// provides an interface for renderers
/// </summary>
class IRenderer
{
	public:
		IRenderer();
		virtual ~IRenderer() {};
		/// <summary>
		/// renders the given pixels
		/// </summary>
		/// <param name="pixels">pixels to render</param>
		virtual void render(render_plane pixels, std::vector<bool> screen_symbols, bool force_rerender) = 0;
		/// <summary>
		/// checks if pixels to render are the same as currently rendered
		/// </summary>
		/// <param name="pixels">pixels to render</param>
		/// <returns>true if same else false</returns>
		bool already_rendered(const render_plane& pixels, const std::vector<bool>& screen_symbols);
	private:
		/// <summary>
		/// currently rendered pixels
		/// </summary>
		render_plane rendered_pixels;
		/// <summary>
		/// currently rendered symbols
		/// </summary>
		std::vector<bool> rendered_screen_symbols;
};