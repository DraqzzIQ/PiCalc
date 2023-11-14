#include "Number.h"

Number::Number()
{
	_rounded = 0;
	_root = new NumberNode();
}


Number::Number(const double value)
{
	_rounded = value;
	_root = new NumberNode();
	_root->value = _rounded;
}

Number::Number(const std::string value)
{
	_rounded = std::stod(value);
	_root = new NumberNode();
	_root->value = _rounded;
}

Number::Number(const Number& other)
{
	_rounded = other._rounded;
	_root = new NumberNode();
	_root->value = _rounded;
}

Number::~Number()
{
	delete _root;
}

Number Number::operator+(const Number& other)
{
	Number result = Number(_rounded + other._rounded);
	return result;
}

Number Number::operator-(const Number& other)
{
	Number result = Number(_rounded - other._rounded);
	return result;
}

Number Number::operator*(const Number& other)
{
	Number result = Number(_rounded * other._rounded);
	return result;
}

Number Number::operator/(const Number& other)
{
	Number result = Number(_rounded / other._rounded);
	return result;
}

Number Number::operator%(const Number& other)
{
	Number result = Number(std::fmod(_rounded, other._rounded));
	return result;
}

Number Number::operator^(const Number& other)
{
	Number result = Number(std::pow(_rounded, other._rounded));
	return result;
}

Number Number::operator+(const double& other)
{
	Number result = Number(_rounded + other);
	return result;
}

Number Number::operator-(const double& other)
{
	Number result = Number(_rounded - other);
	return result;
}

Number Number::operator*(const double& other)
{
	Number result = Number(_rounded * other);
	return result;
}

Number Number::operator/(const double& other)
{
	Number result = Number(_rounded / other);
	return result;
}

Number Number::operator%(const double& other)
{
	Number result = Number(std::fmod(_rounded, other));
	return result;
}

Number Number::operator^(const double& other)
{
	Number result = Number(std::pow(_rounded, other));
	return result;
}

Number Number::operator-()
{
	Number result = Number(-_rounded);
	return result;
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
	_rounded = std::fmod(_rounded, other._rounded);
	return *this;
}

Number& Number::operator^=(const Number& other)
{
	_rounded = std::pow(_rounded, other._rounded);
	return *this;
}

Number& Number::operator=(const Number& other)
{
	_rounded = other._rounded;
	return *this;
}

Number& Number::operator+=(const double& other)
{
	_rounded += other;
	return *this;
}

Number& Number::operator-=(const double& other)
{
	_rounded -= other;
	return *this;
}

Number& Number::operator*=(const double& other)
{
	_rounded *= other;
	return *this;
}

Number& Number::operator/=(const double& other)
{
	_rounded /= other;
	return *this;
}

Number& Number::operator%=(const double& other)
{
	_rounded = std::fmod(_rounded, other);
	return *this;
}

Number& Number::operator^=(const double& other)
{
	_rounded = std::pow(_rounded, other);
	return *this;
}

Number& Number::operator=(const double& other)
{
	_rounded = other;
	return *this;
}

Number& Number::log()
{
	_rounded = std::log10(_rounded);
	return *this;
}


Number& Number::log(const double& other)
{
	_rounded = std::log10(_rounded) / std::log10(other);
	return *this;
}


Number& Number::log(const Number& other)
{
	_rounded = std::log10(_rounded) / std::log10(other._rounded);
	return *this;
}

Number& Number::ln()
{
	_rounded = std::log(_rounded);
	return *this;
}

Number& Number::sin()
{
	_rounded = std::sin(_rounded);
	return *this;
}

Number& Number::cos()
{
	_rounded = std::cos(_rounded);
	return *this;
}

Number& Number::tan()
{
	_rounded = std::tan(_rounded);
	return *this;
}

Number& Number::asin()
{
	_rounded = std::asin(_rounded);
	return *this;
}

Number& Number::acos()
{
	_rounded = std::acos(_rounded);
	return *this;
}

Number& Number::atan()
{
	_rounded = std::atan(_rounded);
	return *this;
}

Number& Number::sinh()
{
	_rounded = std::sinh(_rounded);
	return *this;
}

Number& Number::cosh()
{
	_rounded = std::cosh(_rounded);
	return *this;
}

Number& Number::tanh()
{
	_rounded = std::tanh(_rounded);
	return *this;
}

Number& Number::asinh()
{
	_rounded = std::asinh(_rounded);
	return *this;
}

Number& Number::acosh()
{
	_rounded = std::acosh(_rounded);
	return *this;
}

Number& Number::atanh()
{
	_rounded = std::atanh(_rounded);
	return *this;
}

Number& Number::round()
{
	_rounded = std::round(_rounded);
	return *this;
}

Number& Number::floor()
{
	_rounded = std::floor(_rounded);
	return *this;
}

Number& Number::ceil()
{
	_rounded = std::ceil(_rounded);
	return *this;
}

Number& Number::abs()
{
	_rounded = std::abs(_rounded);
	return *this;
}

Number& Number::to_int()
{
	_rounded = (int)_rounded;
	return *this;
}

Number& Number::negate()
{
	_rounded = -_rounded;
	return *this;
}

Number& Number::pow(const Number& other)
{
	_rounded = std::pow(_rounded, other._rounded);
	return *this;
}

Number& Number::pow(const double& other)
{
	_rounded = std::pow(_rounded, other);
	return *this;
}

Number& Number::factorial()
{
	_rounded = std::tgamma(_rounded + 1);
	return *this;
}

Number& Number::sqrt()
{
	_rounded = std::sqrt(_rounded);
	return *this;
}

Number& Number::root(const Number& other)
{
	_rounded = std::pow(_rounded, 1 / other._rounded);
	return *this;
}

Number& Number::root(const double& other)
{
	_rounded = std::pow(_rounded, 1 / other);
	return *this;
}

Number Number::pol(const Number& first, const Number& second)
{
	Number result = Number(std::sqrt(first._rounded * first._rounded + second._rounded * second._rounded));
	return result;
}

Number Number::rec(const Number& first, const Number& second)
{
	Number result = Number(std::cos(first._rounded) * second._rounded);
	return result;
}

Number Number::gcd(const Number& first, const Number& second)
{
	// gcd (greatest common divisor)
	return Number();
}

Number Number::lcm(const Number& first, const Number& second)
{
	// lcm (least common multiple)
	return Number();
}

Number Number::ran_int(const Number& first, const Number& second)
{
	// random int
	return Number();
}

double Number::get_value() const
{
	return _rounded;
}

Bitset2D Number::render() const
{
	return Graphics::create_text(std::to_string(_rounded));
}
