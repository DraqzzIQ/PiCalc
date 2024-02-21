#pragma once
#include "options/MenuOptionBase.h"
#include <functional>
#include <string>

template <typename T>
class CallbackMenuOption: public MenuOptionBase
{
	public:
	CallbackMenuOption(const std::string& name, T value, std::function<void(T)> callback, KEY select_key = 0)
	{
		this->display_name = name;
		this->select_key = select_key;
		this->_value = value;
		this->_callback = callback;
	}

	void on_select() override
	{
		_callback(_value);
	}

	void on_shift_select() override
	{
		on_select();
	}

	private:
	T _value;
	std::function<void(T)> _callback;
};