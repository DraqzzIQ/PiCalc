#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include "datastructs/Frame.h"
#include "keyboard/KeyPress.h"
#include <algorithm>
#include <stdint.h>
#include <string>
#include <vector>

/// <summary>
/// base class for all windows
/// </summary>
class Window
{
	public:
	Window();
	~Window();
	/// <summary>
	/// updates the window and returns the frame
	/// </summary>
	Frame& update_and_get_frame();
	/// <summary>
	/// called when the window gets rerendered, should update _window and _frame (the Bitset2D in _frame points to _window)
	/// </summary>
	virtual void update_window();
	/// <summary>
	/// handles keydown events
	/// returns true, if the keypress was handled
	/// </summary>
	/// <param name="key">key that got pressed</param>
	virtual bool handle_key_down(KeyPress keypress);
	/// <summary>
	/// handles keyup events
	/// </summary>
	/// <param name="key">key that got released</param>
	virtual bool handle_key_up(KeyPress keypress);
	/// <summary>
	/// copy all data except for the pixels to the given frame
	/// </summary>
	void copy_frame(Frame& frame) const;
	/// <summary>
	/// return _window as const reference
	/// </summary>
	const Bitset2D& get_window() const;

	protected:
	/// <summary>
	/// calles when window is displayed
	/// </summary>
	virtual void got_focus();
	/// <summary>
	/// called when window is not displayed anymore
	/// </summary>
	virtual void lost_focus();

	protected:
	/// <summary>
	/// Bitset2D describing the window
	/// </summary>
	Bitset2D _window;
	/// <summary>
	/// Frame thet is returned on update_and_get_frame(), the Bitset2D in it points to _window
	/// </summary>
	Frame _frame;
	/// <summary>
	/// clears the window
	/// </summary>
	void clear_window();
};
