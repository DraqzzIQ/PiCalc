#pragma once
#include "constant/Error.h"
#include "utils/Utils.h"
#include <cmath>
#include <string>
#include <vector>

#define DECIMAL_VALUE_PRECISION 18
#define DECIMAL_EXP_PRECISION 4
#define DECIMAL_VALUE_MAX 999999999999999999
#define DECIMAL_EXP_MAX 9999

using KEY = uint16_t;

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

	bool add_if_exact(Decimal other);
	bool subtract_if_exact(Decimal other);
	bool multiply_if_exact(Decimal other);
	bool divide_if_exact(Decimal other);
	bool pow_if_exact(Decimal other);

	Decimal& ln();
	Decimal& log(const Decimal& other);
	Decimal& exp();
	Decimal& pow(const Decimal& other);
	Decimal& sqrt();
	Decimal& root(const Decimal& other);
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
	Decimal& ran_int(Decimal start, Decimal end);

	KEY_SET to_key_set_fix(uint8_t fix) const;
	KEY_SET to_key_set_sci(uint8_t sci) const;
	KEY_SET to_key_set_norm(uint8_t norm) const;

	static const Decimal PI;
	static const Decimal EULER;

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
	/// value of the decimal: value = _val * 10^_exp
	/// </summary>
	mutable int64_t _val;
	/// <summary>
	/// exponent of the decimal: value = _val * 10^_exp
	/// </summary>
	mutable int16_t _exp;
};