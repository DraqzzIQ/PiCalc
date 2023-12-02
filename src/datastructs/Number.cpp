// #include "Number.h"
//
// Number::Number()
//{
//	_root = new NumberNode();
// }
//
//
// Number::Number(const double value, const uint16_t exp)
//{
//	_root = new NumberNode();
//	_root->value = value;
// }
//
// Number::Number(const Number& other)
//{
//	_root = other._root->clone();
//
//	_state = other._state;
//	_periodic = other._periodic;
//	_value_cnt = other._value_cnt;
// }
//
// Number::~Number()
//{
//	delete _root;
// }
//
// Number Number::operator+(const Number& other)
//{
//	Number result;
//
//	result._root->value = _root->value + other._root->value;
//	if (other._root->operation != 95 || _root->operation != 95) {
//		result._root->first = _root->clone();
//		result._root->second = other._root->clone();
//	}
//	if (!_simplyfy()) {
//		result._root->value = _root->value + other._root->value;
//	}
//
//	return result;
// }
//
// Number Number::operator-(const Number& other)
//{
//	Number result = Number(_rounded - other._rounded);
//	return result;
// }
//
// Number Number::operator*(const Number& other)
//{
//	Number result = Number(_rounded * other._rounded);
//	return result;
// }
//
// Number Number::operator/(const Number& other)
//{
//	Number result = Number(_rounded / other._rounded);
//	return result;
// }
//
// Number Number::operator%(const Number& other)
//{
//	Number result = Number(std::fmod(_rounded, other._rounded));
//	return result;
// }
//
// Number Number::operator^(const Number& other)
//{
//	Number result = Number(std::pow(_rounded, other._rounded));
//	return result;
// }
//
// Number Number::operator+(const double& other)
//{
//	Number result = Number(_rounded + other);
//	return result;
// }
//
// Number Number::operator-(const double& other)
//{
//	Number result = Number(_rounded - other);
//	return result;
// }
//
// Number Number::operator*(const double& other)
//{
//	Number result = Number(_rounded * other);
//	return result;
// }
//
// Number Number::operator/(const double& other)
//{
//	Number result = Number(_rounded / other);
//	return result;
// }
//
// Number Number::operator%(const double& other)
//{
//	Number result = Number(std::fmod(_rounded, other));
//	return result;
// }
//
// Number Number::operator^(const double& other)
//{
//	Number result = Number(std::pow(_rounded, other));
//	return result;
// }
//
// Number Number::operator-()
//{
//	Number result = Number(-_rounded);
//	return result;
// }
//
// Number& Number::operator+=(const Number& other)
//{
//	_rounded += other._rounded;
//	return *this;
// }
//
// Number& Number::operator-=(const Number& other)
//{
//	_rounded -= other._rounded;
//	return *this;
// }
//
// Number& Number::operator*=(const Number& other)
//{
//	_rounded *= other._rounded;
//	return *this;
// }
//
// Number& Number::operator/=(const Number& other)
//{
//	_rounded /= other._rounded;
//	return *this;
// }
//
// Number& Number::operator%=(const Number& other)
//{
//	_rounded = std::fmod(_rounded, other._rounded);
//	return *this;
// }
//
// Number& Number::operator^=(const Number& other)
//{
//	_rounded = std::pow(_rounded, other._rounded);
//	return *this;
// }
//
// Number& Number::operator=(const Number& other)
//{
//	_rounded_str = other._rounded_str;
//	_rounded = other._rounded;
//	_state = other._state;
//	_root = other._root->clone();
//	return *this;
// }
//
// Number& Number::operator+=(const double& other)
//{
//	_rounded += other;
//	return *this;
// }
//
// Number& Number::operator-=(const double& other)
//{
//	_rounded -= other;
//	return *this;
// }
//
// Number& Number::operator*=(const double& other)
//{
//	_rounded *= other;
//	return *this;
// }
//
// Number& Number::operator/=(const double& other)
//{
//	_rounded /= other;
//	return *this;
// }
//
// Number& Number::operator%=(const double& other)
//{
//	_rounded = std::fmod(_rounded, other);
//	return *this;
// }
//
// Number& Number::operator^=(const double& other)
//{
//	_rounded = std::pow(_rounded, other);
//	return *this;
// }
//
// Number& Number::operator=(const double& other)
//{
//	_rounded = other;
//	return *this;
// }
//
// Number& Number::log()
//{
//	_rounded = std::log10(_rounded);
//	return *this;
// }
//
//
// Number& Number::log(const double& other)
//{
//	_rounded = std::log10(_rounded) / std::log10(other);
//	return *this;
// }
//
//
// Number& Number::log(const Number& other)
//{
//	_rounded = std::log10(_rounded) / std::log10(other._rounded);
//	return *this;
// }
//
// Number& Number::ln()
//{
//	_rounded = std::log(_rounded);
//	return *this;
// }
//
// Number& Number::sin()
//{
//	_rounded = std::sin(_rounded);
//	return *this;
// }
//
// Number& Number::cos()
//{
//	_rounded = std::cos(_rounded);
//	return *this;
// }
//
// Number& Number::tan()
//{
//	_rounded = std::tan(_rounded);
//	return *this;
// }
//
// Number& Number::asin()
//{
//	_rounded = std::asin(_rounded);
//	return *this;
// }
//
// Number& Number::acos()
//{
//	_rounded = std::acos(_rounded);
//	return *this;
// }
//
// Number& Number::atan()
//{
//	_rounded = std::atan(_rounded);
//	return *this;
// }
//
// Number& Number::sinh()
//{
//	_rounded = std::sinh(_rounded);
//	return *this;
// }
//
// Number& Number::cosh()
//{
//	_rounded = std::cosh(_rounded);
//	return *this;
// }
//
// Number& Number::tanh()
//{
//	_rounded = std::tanh(_rounded);
//	return *this;
// }
//
// Number& Number::asinh()
//{
//	_rounded = std::asinh(_rounded);
//	return *this;
// }
//
// Number& Number::acosh()
//{
//	_rounded = std::acosh(_rounded);
//	return *this;
// }
//
// Number& Number::atanh()
//{
//	_rounded = std::atanh(_rounded);
//	return *this;
// }
//
// Number& Number::round()
//{
//	_rounded = std::round(_rounded);
//	return *this;
// }
//
// Number& Number::floor()
//{
//	_rounded = std::floor(_rounded);
//	return *this;
// }
//
// Number& Number::ceil()
//{
//	_rounded = std::ceil(_rounded);
//	return *this;
// }
//
// Number& Number::abs()
//{
//	_rounded = std::abs(_rounded);
//	return *this;
// }
//
// Number& Number::to_int()
//{
//	_rounded = (int)_rounded;
//	return *this;
// }
//
// Number& Number::negate()
//{
//	_rounded = -_rounded;
//	return *this;
// }
//
// Number& Number::pow(const Number& other)
//{
//	_rounded = std::pow(_rounded, other._rounded);
//	return *this;
// }
//
// Number& Number::pow(const double& other)
//{
//	_rounded = std::pow(_rounded, other);
//	return *this;
// }
//
// Number& Number::factorial()
//{
//	_rounded = std::tgamma(_rounded + 1);
//	return *this;
// }
//
// Number& Number::sqrt()
//{
//	_rounded = std::sqrt(_rounded);
//	return *this;
// }
//
// Number& Number::root(const Number& other)
//{
//	_rounded = std::pow(_rounded, 1 / other._rounded);
//	return *this;
// }
//
// Number& Number::root(const double& other)
//{
//	_rounded = std::pow(_rounded, 1 / other);
//	return *this;
// }
//
// Number Number::pol(const Number& first, const Number& second)
//{
//	Number result = Number(std::sqrt(first._rounded * first._rounded + second._rounded * second._rounded));
//	return result;
// }
//
// Number Number::rec(const Number& first, const Number& second)
//{
//	Number result = Number(std::cos(first._rounded) * second._rounded);
//	return result;
// }
//
// Number Number::gcd(const Number& first, const Number& second)
//{
//	// gcd (greatest common divisor)
//	return Number();
// }
//
// Number Number::lcm(const Number& first, const Number& second)
//{
//	// lcm (least common multiple)
//	return Number();
// }
//
// Number Number::ran_int(const Number& first, const Number& second)
//{
//	// random int
//	return Number();
// }
//
// double Number::get_value() const
//{
//	return _rounded;
// }
//
// bool Number::add_digit(const uint8_t digit)
//{
//	if (_state & 0b1000) {
//		Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
//	} else if (digit < 10) {
//		if (_state & 0b010) _root->exp = _root->exp * 10 + digit;
//		else {
//			if (_state & 0b001) _root->exp--;
//			else if (_state & 0b100) _periodic = _periodic * 10 + digit;
//			_root->value = _root->value * 10 + digit;
//		}
//	} else if (digit == 82) {
//		if (_state & 0b111) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
//		_state |= 0b001;
//	} else if (digit == 127) {
//		if (_state & 0b110) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
//		_state |= 0b0010;
//	} else if (digit == 133) {
//		if (!(_state & 0b001) || _state & 0b010) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
//		if (_state & 0b100) _state |= 0b1000;
//		else _state |= 0b100;
//	} else return false;
//	_value_cnt++;
//	return true;
// }
//
// uint16_t Number::finalize()
//{
//	if (!_value_cnt || ((_state & 0b100) && !_periodic)) return 0;
//	if (_state & 0b100) {
//		// TODO
//	} else {
//		_root->operation = 0;
//		_root->first = nullptr;
//		_root->second = nullptr;
//	}
//
//	_periodic = 0;
//	_state = 0;
//	_value_cnt = 0;
//	return _value_cnt;
// }
//
// Bitset2D Number::render() const
//{
//	return Graphics::create_text(std::to_string(_root));
// }
//
// bool Number::_simplyfy()
//{
//	// TODO
//	return false;
// }
