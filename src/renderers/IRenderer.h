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
	virtual void render(Frame frame, bool force_rerender) = 0;
	/// <summary>
	/// sets the contrast of the display on the pico, does nothing on other platforms
	/// </summary>
	virtual void set_contrast(uint8_t value);
	/// <summary>
	/// returns the current contrast of the display on the pico, returns 255 on other platforms
	/// </summary>
	virtual uint8_t get_contrast();
	/// <summary>
	/// checks if frame to render is the same as currently rendered
	/// </summary>
	/// <param name="frame">frame to check</param>
	/// <returns>true if same else false</returns>
	bool already_rendered(Frame frame);

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
