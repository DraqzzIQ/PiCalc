#pragma once
#include "constant/Error.h"
#include "utils/Utils.h"
#include <cmath>
#include <string>
#include <vector>

constexpr uint8_t DECIMAL_VALUE_PRECISION = 18;
constexpr uint8_t DECIMAL_EXP_PRECISION = 4;
constexpr int64_t DECIMAL_VALUE_MAX = 999999999999999999;
constexpr int16_t DECIMAL_EXP_MAX = 9999;

/// <summary>
/// stores either a KEY or a decimal: value = _val * 10 ^ _exp<para/>
/// IMPORTANT: don't use any operations if the decimal represents a KEY
/// </summary>
class Decimal
{
	public:
	Decimal();
	Decimal(int64_t value);
	Decimal(int64_t value, int16_t exp);
	Decimal(const Decimal& other);

	void set_key(KEY value);
	void set_value(int64_t value, int16_t exp);

	bool is_key() const;
	KEY get_key() const;
	int64_t get_value() const;
	int16_t get_exp() const;

	bool operator==(Decimal other) const;
	bool operator!=(Decimal other) const;
	bool operator<(Decimal other) const;
	bool operator>(Decimal other) const;
	bool operator<=(Decimal other) const;
	bool operator>=(Decimal other) const;

	Decimal operator-() const;
	Decimal& operator=(Decimal other);
	Decimal& operator=(int64_t other);

	Decimal operator+(Decimal other) const;
	Decimal operator-(Decimal other) const;
	Decimal operator*(Decimal other) const;
	Decimal operator/(Decimal other) const;
	Decimal operator%(Decimal other) const;
	Decimal operator^(Decimal other) const;

	Decimal& operator+=(Decimal other);
	Decimal& operator-=(Decimal other);
	Decimal& operator*=(Decimal other);
	Decimal& operator/=(Decimal other);
	Decimal& operator%=(Decimal other);
	Decimal& operator^=(Decimal other);

	Decimal& ln();
	Decimal& log(Decimal other);
	Decimal& exp();
	Decimal& sqrt();
	Decimal& root(Decimal other);
	Decimal& factorial();

	Decimal& sin();
	Decimal& cos();
	Decimal& tan();
	Decimal& asin();
	Decimal& acos();
	Decimal& atan();
	Decimal& sinh();
	Decimal& cosh();
	Decimal& tanh();
	Decimal& asinh();
	Decimal& acosh();
	Decimal& atanh();

	Decimal& round();
	Decimal& floor();
	Decimal& ceil();
	Decimal& to_int();
	Decimal& abs();
	Decimal& negate();
	Decimal& ran();
	Decimal& ran_int(Decimal end);

	/// <summary>
	/// rectangular to polar coordinates (this = x, other = y)
	/// </summary>
	Decimal& pol(Decimal other);
	/// <summary>
	/// polar to rectangular coordinates (this = r, other = theta)
	/// </summary>
	Decimal& rec(Decimal other);
	/// <summary>
	/// greatest common divisor
	/// </summary>
	Decimal& gcd(Decimal other);
	/// <summary>
	/// least common multiple
	/// </summary>
	Decimal& lcm(Decimal other);

	/// <summary>
	/// turns the value into a KEY_SET and appends it to res
	/// </summary>
	/// <param name="res"></param>
	void value_to_key_set(KEY_SET& res) const;
	/// <summary>
	/// turns the exponent into a KEY_SET and appends it to res
	/// </summary>
	/// <param name="res"></param>
	void exp_to_key_set(KEY_SET& res) const;
	/// <summary>
	/// returns a KEY_SET representing the decimal
	/// </summary>
	/// <param name="mode">1: norm (count = max lost digits), 2: fix (count = number of decimal places), 3: sci (count = number of digits)</param>
	/// <param name="count">depends on mode</param>
	/// <param name="max_size">max size of the output KEY_SET</param>
	/// <returns></returns>
	KEY_SET to_key_set(uint8_t max_size) const;

	/// <summary>
	/// approximation of pi
	/// </summary>
	static const Decimal PI;
	/// <summary>
	/// approximation of e
	/// </summary>
	static const Decimal EULER;
	/// <summary>
	/// approximation of ln(10)
	/// </summary>
	static const Decimal LN10;
	/// <summary>
	/// contains all values for 10^n with n from 0 to 18
	/// </summary>
	static const int64_t powers_of_ten[19];

	private:
	/// <summary>
	/// count the number of digits after the first non-zero digit (base 10)
	/// </summary>
	static uint8_t count_digits(int64_t value);
	/// <summary>
	/// count the number of digits after the first non-zero digit (base 10)
	/// </summary>
	static uint8_t count_digits_unsigned(uint64_t value);
	/// <summary>
	/// shifts the value to the right by shift and rounds the last digit
	/// </summary>
	/// <param name="shift">range: 1 to DECIMAL_VALUE_PRECISION (inclusive)</param>
	static void shift_right(int64_t& value, uint8_t shift);
	/// <summary>
	/// shifts the value to the right by shift
	/// </summary>
	/// <param name="shift">range: 1 to DECIMAL_VALUE_PRECISION (inclusive)</param>
	static void shift_right(uint64_t& value, uint8_t shift);
	/// <summary>
	/// shifts the value to the right by one and rounds the last digit
	/// </summary>
	/// <param name="value"></param>
	static void shift_right_one(int64_t& value);
	/// <summary>
	/// maximize the exponent as much as possible without loosing precision
	/// </summary>
	void maximize_exp() const;
	/// <summary>
	/// add other to this while adding the next digit to error if necessary and returning whether the value or error changed
	/// </summary>
	bool add_changed(Decimal other);
	uint8_t exp_count_digits() const;

	/// <summary>
	/// value of the decimal: value = _val * 10^_exp
	/// </summary>
	mutable int64_t _val;
	/// <summary>
	/// exponent of the decimal: value = _val * 10^_exp
	/// </summary>
	mutable int16_t _exp;
};