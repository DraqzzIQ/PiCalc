#include "Number.h"

Number::Number()
{
	_root = nullptr;
}

Number::Number(const int64_t value, const int16_t exp)
{
	_root = new NumberNode();
	_root->value = value * std::pow(10, exp);
}

Number::Number(const Number& other)
{
	_root = other._root->clone();
}

Number::~Number()
{
	delete _root;
}

Number& Number::operator+=(Number& other)
{
	if (_root->operation == 95 && other._root->operation == 95) {
		_root->value += other._root->value;
	} else if (_root->operation == 69 && other._root->operation == 69) {
		std::copy(other._root->children.begin(), other._root->children.end(), _root->children.end());
	} else if (_root->operation == 69) {
		_root->children.push_back(other._root);
	} else if (other._root->operation == 69) {
		other._root->children.push_back(_root);
		_root = other._root;
	} else {
		_root = new NumberNode{ 0, 69, std::vector<NumberNode*>{ _root, other._root } };
	}
	return *this;
}

Number& Number::operator-=(Number& other)
{
	other.negate();
	*this += other;
	return *this;
}

Number& Number::operator*=(Number& other)
{
	if (_root->operation == 95 && other._root->operation == 95) {
		_root->value *= other._root->value;
	} else if (_root->operation == 71 && other._root->operation == 71) {
		std::copy(other._root->children.begin(), other._root->children.end(), _root->children.end());
	} else if (_root->operation == 71) {
		_root->children.push_back(other._root);
	} else if (other._root->operation == 71) {
		other._root->children.push_back(_root);
		_root = other._root;
	} else {
		_root = new NumberNode{ 0, 71, std::vector<NumberNode*>{ _root, other._root } };
	}
	return *this;
}

Number& Number::operator/=(Number& other)
{
	_rounded /= other._rounded;
	return *this;
}

Number& Number::operator%=(Number& other)
{
	_rounded = std::fmod(_rounded, other._rounded);
	return *this;
}

Number& Number::operator^=(Number& other)
{
	_rounded = std::pow(_rounded, other._rounded);
	return *this;
}

Number& Number::operator=(const Number& other)
{
	_root = other._root->clone();
	return *this;
}

Number& Number::log()
{
	_rounded = std::log10(_rounded);
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

double Number::simplify()
{
	return false;
}

double Number::to_value() const
{
	return _rounded;
}

std::vector<KEY_SET> Number::to_key_set() const
{
	return std::vector<KEY_SET>();
}