#pragma once
#include "constant/Error.h"
#include <cmath>
#include <string>
#include <vector>

#define DECIMAL_VALUE_PRECISION 15
#define DECIMAL_EXP_PRECISION 3
#define DECIMAL_VALUE_MAX 999999999999999
#define DECIMAL_EXP_MAX 999

/// <summary>
/// stores either a KEY or a decimal of the form val * 10 ^ exp
/// </summary>
class Decimal
{
	public:
	Decimal();
	Decimal(KEY value);
	Decimal(int64_t value, int16_t exp);

	void set_key(KEY value);
	void set_value(int64_t value, int16_t exp);

	inline bool is_zero() const;
	inline bool is_negative() const;
	inline bool is_key() const;

	KEY get_key() const;
	int64_t get_value() const;
	int16_t get_exp() const;

	bool operator==(Decimal& other);
	bool operator!=(Decimal& other);
	bool operator<(Decimal& other);
	bool operator>(Decimal& other);
	bool operator<=(Decimal& other);
	bool operator>=(Decimal& other);

	Decimal operator-();
	Decimal& operator=(const Decimal& other);

	Decimal operator+(const Decimal& other) const;
	Decimal operator-(const Decimal& other) const;
	Decimal operator*(const Decimal& other) const;
	Decimal operator/(const Decimal& other) const;
	Decimal operator%(const Decimal& other) const;
	Decimal operator^(const Decimal& other) const;

	Decimal& operator+=(const Decimal& other);
	Decimal& operator-=(const Decimal& other);
	Decimal& operator*=(const Decimal& other);
	Decimal& operator/=(const Decimal& other);
	Decimal& operator%=(const Decimal& other);
	Decimal& operator^=(const Decimal& other);

	Decimal& log();
	Decimal& log(const double& other);
	Decimal& log(const Decimal& other);
	Decimal& ln();

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
	Decimal& abs();
	Decimal& to_int();
	Decimal& negate();

	Decimal& pow(const Decimal& other);
	Decimal& pow(const double& other);
	Decimal& factorial();

	Decimal& sqrt();
	Decimal& root(const Decimal& other);
	Decimal& root(const double& other);

	private:
	static const uint64_t move_comma[DECIMAL_VALUE_PRECISION];
	/// <summary>
	/// maximize the exponent as much as possible without loosing precision
	/// </summary>
	void maximize_exp();
	/// <summary>
	/// minimize the exponent as much as possible without loosing precision
	/// </summary>
	void minimize_exp();
	void shift_comma(int8_t shift);
	void change_accuracy(int8_t shift);

	/// <summary>
	/// right to left: 0-51: value (52 bits); 52-62: exponent (11 bits); 63: is KEY? <para/>
	/// normally: value = value * 10 ^ exponent<para/>
	/// if bit 63 is 1: this represents a KEY, so bits 0-15 represent a uint16_t
	/// </summary>
	uint64_t _value;
};