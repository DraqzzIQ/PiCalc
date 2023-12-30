#include "Number.h"

Number::Number()
{
	_value = 0;
	_operation = 95;
	_children = std::vector<Number*>();
}

Number::Number(const int64_t value, const int16_t exp)
{
	_value = value * std::pow(10, exp);
	_operation = 95;
	_children = std::vector<Number*>();
}

Number::Number(const Number* other)
{
	operator=(other);
}

Number::Number(double value)
{
	_value = value;
	_operation = 95;
	_children = std::vector<Number*>();
}

Number::~Number()
{
	for (Number* child : _children) delete child;
}

Number* Number::operator=(const Number* other)
{
	_value = other->_value;
	_operation = other->_operation;
	_children = std::vector<Number*>();
	for (Number* child : other->_children) _children.push_back(child->deep_clone());
	return this;
}

Number* Number::add(Number* other)
{
	if (_operation == 69 && other->_operation == 69) {
		for (Number* child : other->_children) _children.push_back(child);
	} else if (_operation == 69) {
		_children.push_back(other);
	} else if (other->_operation == 69) {
		_children = std::vector<Number*>{ clone() };
		for (Number* child : other->_children) _children.push_back(child);
		_value = 0;
		_operation = 69;
	} else {
		_children = std::vector<Number*>{ clone(), other->clone() };
		_value = 0;
		_operation = 69;
	}
	other = nullptr;
	return this;
}

Number* Number::subtract(Number* other)
{
	add(other->negate());
	other = nullptr;
	return this;
}

Number* Number::multiply(Number* other)
{
	if (_operation == 71 && other->_operation == 71) {
		for (Number* child : other->_children) _children.push_back(child);
	} else if (_operation == 71) {
		_children.push_back(other);
	} else if (other->_operation == 71) {
		_children = std::vector<Number*>{ clone() };
		for (Number* child : other->_children) _children.push_back(child);
		_value = 0;
		_operation = 71;
	} else {
		_children = std::vector<Number*>{ clone(), other->clone() };
		_value = 0;
		_operation = 71;
	}
	other = nullptr;
	return this;
}

Number* Number::divide(Number* other)
{
	_children = std::vector<Number*>{ clone(), other->clone() };
	_value = 0;
	_operation = 72;
	other = nullptr;
	return this;
}

Number* Number::mod(Number* other)
{
	return this;
}


Number* Number::log()
{
	return this;
}

Number* Number::log(Number* other)
{
	return this;
}

Number* Number::ln()
{
	return this;
}


Number* Number::sin()
{
	return this;
}

Number* Number::cos()
{
	return this;
}

Number* Number::tan()
{
	return this;
}

Number* Number::asin()
{
	return this;
}

Number* Number::acos()
{
	return this;
}

Number* Number::atan()
{
	return this;
}

Number* Number::sinh()
{
	return this;
}

Number* Number::cosh()
{
	return this;
}

Number* Number::tanh()
{
	return this;
}

Number* Number::asinh()
{
	return this;
}

Number* Number::acosh()
{
	return this;
}

Number* Number::atanh()
{
	return this;
}


Number* Number::round()
{
	return this;
}

Number* Number::floor()
{
	return this;
}

Number* Number::ceil()
{
	return this;
}

Number* Number::abs()
{
	return this;
}

Number* Number::to_int()
{
	return this;
}

Number* Number::negate()
{
	return this;
}

Number* Number::percent()
{
	return this;
}


Number* Number::pow(Number* other)
{
	return this;
}

Number* Number::pow10()
{
	return this;
}

Number* Number::exp()
{
	return this;
}

Number* Number::factorial()
{
	return this;
}


Number* Number::root(Number* other)
{
	return this;
}

Number* Number::sqrt()
{
	return this;
}


Number* Number::pol(Number* other)
{
	return this;
}

Number* Number::rec(Number* other)
{
	return this;
}

Number* Number::gcd(Number* other)
{
	return this;
}

Number* Number::lcm(Number* other)
{
	return this;
}

Number* Number::ran_int(Number* other)
{
	return this;
}

void Number::simplify()
{
	return;
}

double Number::to_value() const
{
	return 0;
}

std::vector<KEY_SET> Number::to_key_set() const
{
	return std::vector<KEY_SET>();
}


Number* Number::clone() const
{
	Number* clone = new Number();
	clone->_value = _value;
	clone->_operation = _operation;
	for (Number* child : _children) clone->_children.push_back(child);
	return clone;
}

Number* Number::deep_clone() const
{
	if (_operation) {
		Number* clone = new Number();
		clone->_value = _value;
		clone->_operation = _operation;
		for (Number* child : _children) clone->_children.push_back(child->deep_clone());
		return clone;
	} else return nullptr;
}