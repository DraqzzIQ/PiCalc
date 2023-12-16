#pragma once
#include "constant/Error.h"
#include <cmath>
#include <string>
#include <vector>

#define DECIMAL_VALUE_PRECISION 19
#define DECIMAL_EXP_PRECISION 4
#define DECIMAL_VALUE_MAX 9999999999999999999
#define DECIMAL_EXP_MAX 9999

class Decimal
{
	public:
	Decimal();
	Decimal(double value);
	Decimal(int64_t value, int16_t exp);

	bool operator==(const Decimal& other) const;
	bool operator!=(const Decimal& other) const;
	bool operator<(const Decimal& other) const;
	bool operator>(const Decimal& other) const;
	bool operator<=(const Decimal& other) const;
	bool operator>=(const Decimal& other) const;

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

	uint8_t sign() const;

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
	void normalize();
	void shift_comma(int8_t shift);
	void change_accuracy(int8_t shift);
	uint64_t move_comma[DECIMAL_VALUE_PRECISION] = {
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
		10000000000,
		100000000000,
		1000000000000,
		10000000000000,
		100000000000000,
		1000000000000000,
		10000000000000000,
		100000000000000000,
		1000000000000000000,
	};
	int64_t _value;
	int16_t _number_exp;
};