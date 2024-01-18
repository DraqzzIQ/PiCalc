#pragma once
#include "options/MenuOptionBase.h"
#include <functional>
#include <string>

template <typename T>
class CallbackMenuOption: public MenuOptionBase
{
	public:
	CallbackMenuOption(const std::string& name, T value, std::function<void(T)> callback)
	{
		this->_display_name = name;
		this->_value = value;
		this->_callback = callback;
	}
	~CallbackMenuOption() = default;

	void on_select()
	{
		_callback(_value);
		delete this;
	}

	void on_shift_select()
	{
		on_select();
	}

	std::string get_display_name()
	{
		return _display_name;
	}

	bool open_window()
	{
		return false;
	}

	private:
	std::string _display_name;
	T _value;
	std::function<void(T)> _callback;
};