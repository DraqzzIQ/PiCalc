#pragma once
#include <cmath>
#include <string>
#include <vector>

class Decimal
{
public:
	Decimal();
	Decimal(double value);
	Decimal(int64_t value, int16_t exp);

	Decimal operator+(const Decimal& other);
	Decimal operator-(const Decimal& other);
	Decimal operator*(const Decimal& other);
	Decimal operator/(const Decimal& other);
	Decimal operator%(const Decimal& other);
	Decimal operator^(const Decimal& other);

	Decimal operator+(const double& other);
	Decimal operator-(const double& other);
	Decimal operator*(const double& other);
	Decimal operator/(const double& other);
	Decimal operator%(const double& other);
	Decimal operator^(const double& other);

	Decimal operator-();

	Decimal& operator+=(const Decimal& other);
	Decimal& operator-=(const Decimal& other);
	Decimal& operator*=(const Decimal& other);
	Decimal& operator/=(const Decimal& other);
	Decimal& operator%=(const Decimal& other);
	Decimal& operator^=(const Decimal& other);
	Decimal& operator=(const Decimal& other);

	Decimal& operator+=(const double& other);
	Decimal& operator-=(const double& other);
	Decimal& operator*=(const double& other);
	Decimal& operator/=(const double& other);
	Decimal& operator%=(const double& other);
	Decimal& operator^=(const double& other);
	Decimal& operator=(const double& other);

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
	uint64_t _value;
};

