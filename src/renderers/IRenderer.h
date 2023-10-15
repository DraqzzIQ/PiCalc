#pragma once
#include "constant\Constants.h"
#include "constant\Graphics.h"
#include <stddef.h>

/// <summary>
/// provides an interface for renderers
/// </summary>
class IRenderer
{
	public:
	IRenderer();
	virtual ~IRenderer(){};
	/// <summary>
	/// renders the given pixels
	/// </summary>
	/// <param name="pixels">pixels to render</param>
	virtual void render(const Bitset2D& pixels, const DynamicBitset& screen_symbols, bool force_rerender) = 0;
	/// <summary>
	/// checks if pixels to render are the same as currently rendered
	/// </summary>
	/// <param name="pixels">pixels to render</param>
	/// <returns>true if same else false</returns>
	bool already_rendered(const Bitset2D& pixels, const DynamicBitset& screen_symbols);

	private:
	/// <summary>
	/// currently rendered pixels
	/// </summary>
	Bitset2D rendered_pixels;
	/// <summary>
	/// currently rendered symbols
	/// </summary>
	DynamicBitset rendered_screen_symbols;
};
