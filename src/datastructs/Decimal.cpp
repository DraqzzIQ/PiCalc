#if false

#include "Decimal.h"

Decimal::Decimal()
{
	_value = 0;
	_exp = 0;
}

Decimal::Decimal(double value)
{
	_exp = (value == 0) ? 0 : 1 + (int16_t)std::floor(std::log10(std::fabs(value)));
	_value = value * std::pow(10, -_exp);
	normalize();
}

Decimal::Decimal(int64_t value, int16_t exp)
{
	if (std::abs(value) > DECIMAL_VALUE_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	if (std::abs(exp) > DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	_exp = (value == 0) ? 0 : exp;
	_value = value;
	normalize();
}

bool Decimal::operator==(const Decimal& other) const
{
	return _value == other._value && _exp == other._exp;
}

bool Decimal::operator!=(const Decimal& other) const
{
	return _value != other._value || _exp != other._exp;
}

bool Decimal::operator<(const Decimal& other) const
{
	if (sign() > other.sign()) return false;
	if (sign() < other.sign()) return true;
	if (sign() == 0) return false;
	if (sign() == 1) {
		if (_exp > other._exp + DECIMAL_VALUE_PRECISION) return false;
		if (_exp + DECIMAL_VALUE_PRECISION < other._exp) return true;
		if (_value * std::pow(10, _exp) < other._value * std::pow(10, other._exp)) return true;
		else return false;
	} else {
		if (_exp > other._exp + DECIMAL_VALUE_PRECISION) return true;
		if (_exp + DECIMAL_VALUE_PRECISION < other._exp) return false;
		if (_value * std::pow(10, _exp) < other._value * std::pow(10, other._exp)) return false;
		else return true;
	}
}

bool Decimal::operator>(const Decimal& other) const
{
	return !(*this < other);
}

bool Decimal::operator<=(const Decimal& other) const
{
	return *this < other || *this == other;
}

bool Decimal::operator>=(const Decimal& other) const
{
	return *this > other || *this == other;
}

Decimal Decimal::operator-()
{
	return Decimal(-_value, _exp);
}

Decimal& Decimal::operator=(const Decimal& other)
{
	_value = other._value;
	_exp = other._exp;
	return *this;
}

Decimal Decimal::operator+(const Decimal& other) const
{
	if (sign() == 0) return Decimal(other);
	if (other.sign() == 0) return Decimal(*this);
	if (_exp - other._exp > DECIMAL_VALUE_PRECISION * 2) return Decimal(*this);
	if (other._exp - _exp > DECIMAL_VALUE_PRECISION * 2) return Decimal(other);

	Decimal result = Decimal(*this);
	Decimal add = Decimal(other);
	result.change_accuracy(_exp - other._exp);
	add.change_accuracy(other._exp - _exp);
	if (DECIMAL_VALUE_MAX - result._value < add._value) {
		result.change_accuracy(-1);
		add.change_accuracy(-1);
	}
	result._value += add._value;
}

uint8_t Decimal::sign() const
{
	if (_value > 0) return 1;
	else if (_value < 0) return -1;
	else return 0;
}

void Decimal::normalize()
{
	if (_value == 0) _exp = 0;
	while (_value > 0 && _value % 10 == 0) {
		_value *= 10;
		_exp--;
	}
}

void Decimal::shift_comma(int8_t shift)
{
	_exp += shift;
}

void Decimal::change_accuracy(int8_t shift)
{
	if (shift == 0 || std::abs(shift) > 18) return;
	else if (shift > 0) {
		while (shift > 0 && _value > move_comma[DECIMAL_VALUE_PRECISION - shift + 1]) shift--;
		_value *= move_comma[shift];
		_exp -= shift;
	} else {
		int64_t old_value = _value;
		_value /= move_comma[-shift];
		_exp += shift;
		if ((_value * 10 + 5) * move_comma[-shift - 1] < old_value) _value++;
	}
}

#endif