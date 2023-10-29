#include "Number.h"

Number::Number()
{
	_rounded = 0;
}

Number::Number(double value)
{
	_rounded = value;
}

Number::Number(int64_t value)
{
	_rounded = value;
}

Number::Number(std::vector<uint8_t> values)
{
	_rounded = 0;
	for (uint8_t value : values)
	{
		_rounded *= 10;
		_rounded += value;
	}
}

Number::~Number()
{
}

Number Number::operator+(const Number& other)
{
	return Number(_rounded + other._rounded);
}

Number Number::operator-(const Number& other)
{
	return Number(_rounded - other._rounded);
}

Number Number::operator*(const Number& other)
{
	return Number(_rounded * other._rounded);
}

Number Number::operator/(const Number& other)
{
	return Number(_rounded / other._rounded);
}

Number Number::operator%(const Number& other)
{
	return Number(fmod(_rounded, other._rounded));
}

Number Number::operator^(const Number& other)
{
	return Number(pow(_rounded, other._rounded));
}

Number& Number::operator+=(const Number& other)
{
	_rounded += other._rounded;
	return *this;
}

Number& Number::operator-=(const Number& other)
{
	_rounded -= other._rounded;
	return *this;
}

Number& Number::operator*=(const Number& other)
{
	_rounded *= other._rounded;
	return *this;
}

Number& Number::operator/=(const Number& other)
{
	_rounded /= other._rounded;
	return *this;
}

Number& Number::operator%=(const Number& other)
{
	_rounded = fmod(_rounded, other._rounded);
	return *this;
}

Number& Number::operator^=(const Number& other)
{
	_rounded = pow(_rounded, other._rounded);
	return *this;
}

Number Number::operator-()
{
	return Number(-_rounded);
}

bool Number::operator==(const Number& other)
{
	return _rounded == other._rounded;
}

bool Number::operator!=(const Number& other)
{
	return _rounded != other._rounded;
}

bool Number::operator<(const Number& other)
{
	return _rounded < other._rounded;
}

bool Number::operator>(const Number& other)
{
	return _rounded > other._rounded;
}

bool Number::operator<=(const Number& other)
{
	return _rounded <= other._rounded;
}

bool Number::operator>=(const Number& other)
{
	return _rounded >= other._rounded;
}
