#pragma once
#include "datastructs/Number.h"

class NumberParser
{
	public:
	NumberParser();
	~NumberParser();

	void clear_number();
	bool add_digit(KEY digit);
	uint8_t get_value_cnt();
	Number* get_number();

	private:
	/// <summary>
	/// exponent of the decimal currently being converted
	/// </summary>
	int16_t _exp;
	/// <summary>
	/// value of the decimal currently being converted
	/// </summary>
	int64_t _val;
	/// <summary>
	/// right to left:<para/>
	/// 0-4: number of periodic digits<para/>
	/// 5: periodic active?<para/>
	/// 6: comma placed?<para/>
	/// 7: exp placed?
	/// </summary>
	uint8_t _state = 0;
	/// <summary>
	/// right to left:<para/>
	/// 0-5: number of symbols placed<para/>
	/// 6: exp negative?<para/>
	/// 7: digits placed after exp?
	/// </summary>
	uint8_t _value_cnt = 0;
};
