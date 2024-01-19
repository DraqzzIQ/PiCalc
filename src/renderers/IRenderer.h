#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "datastructs/Frame.h"
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
	/// renders the given frame
	/// </summary>
	/// <param name="frame">frame to render</param>
	virtual void render(const Frame& frame, bool force_rerender) = 0;
	/// <summary>
	/// checks if frame to render is the same as currently rendered
	/// </summary>
	/// <param name="frame">frame to check</param>
	/// <returns>true if same else false</returns>
	bool already_rendered(const Frame& frame);

	/// <summary>
	/// holds all renderers
	/// </summary>
	static std::vector<IRenderer*> Renderers;

	private:
	/// <summary>
	/// currently rendered frame
	/// </summary>
	Frame _rendered_frame;
};
