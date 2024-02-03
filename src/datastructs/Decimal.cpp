#include "datastructs/Decimal.h"

// TODO

const int64_t Decimal::powers_of_ten[] = {
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
	1000000000000000000
};

const Decimal Decimal::PI(314159265358979324, -17);
const Decimal Decimal::EULER(271828182845904524, -17);
const Decimal Decimal::LN10(230258509299404568, -17);


Decimal::Decimal()
{
	_val = 0;
	_exp = 0;
}

Decimal::Decimal(int64_t value)
{
	if (std::abs(value) > DECIMAL_VALUE_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	_exp = 0;
	_val = value;
}

Decimal::Decimal(int64_t value, int16_t exp)
{
	if (std::abs(value) > DECIMAL_VALUE_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	if (std::abs(exp) > DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	_exp = (value == 0) ? 0 : exp;
	_val = value;
}

Decimal::Decimal(const Decimal& other)
{
	_val = other._val;
	_exp = other._exp;
}


void Decimal::set_key(KEY value)
{
	_exp = value;
	_val = 0x7fffffffffffffff;
}

void Decimal::set_value(int64_t value, int16_t exp)
{
	if (std::abs(value) > DECIMAL_VALUE_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	if (std::abs(exp) > DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	_exp = (value == 0) ? 0 : exp;
	_val = value;
}


bool Decimal::is_key() const
{
	return _val == 0x7fffffffffffffff;
}


KEY Decimal::get_key() const
{
	if (_val != 0x7fffffffffffffff) return 0;
	return (KEY)_exp;
}

int64_t Decimal::get_value() const
{
	return _val;
}

int16_t Decimal::get_exp() const
{
	return _exp;
}


bool Decimal::operator==(Decimal other) const
{
	maximize_exp();
	other.maximize_exp();
	return _val == other._val && _exp == other._exp;
}

bool Decimal::operator!=(Decimal other) const
{
	maximize_exp();
	other.maximize_exp();
	return _val != other._val || _exp != other._exp;
}

bool Decimal::operator<(Decimal other) const
{
	Decimal res = operator-(other);
	return res._val < 0;
}

bool Decimal::operator>(Decimal other) const
{
	Decimal res = operator-(other);
	return res._val > 0;
}

bool Decimal::operator<=(Decimal other) const
{
	Decimal res = operator-(other);
	return res._val <= 0;
}

bool Decimal::operator>=(Decimal other) const
{
	Decimal res = operator-(other);
	return res._val >= 0;
}

Decimal Decimal::operator-() const
{
	return Decimal(-_val, _exp);
}

Decimal& Decimal::operator=(Decimal other)
{
	_val = other._val;
	_exp = other._exp;
	return *this;
}

Decimal& Decimal::operator=(int64_t other)
{
	_val = other;
	_exp = 0;
	return *this;
}


Decimal Decimal::operator+(Decimal other) const
{
	other += *this;
	return other;
}

Decimal Decimal::operator-(Decimal other) const
{
	other.negate();
	other += *this;
	return other;
}

Decimal Decimal::operator*(Decimal other) const
{
	other *= *this;
	return other;
}

Decimal Decimal::operator/(Decimal other) const
{
	Decimal res = *this;
	res /= other;
	return res;
}

Decimal Decimal::operator%(Decimal other) const
{
	Decimal res = *this;
	res %= other;
	return res;
}

Decimal Decimal::operator^(Decimal other) const
{
	Decimal res = *this;
	res ^= other;
	return res;
}


Decimal& Decimal::operator+=(Decimal other)
{
	// if one value is zero, return the other one
	if (_val == 0) {
		_val = other._val;
		_exp = other._exp;
		return *this;
	}
	if (other._val == 0) return *this;

	// if the exponents are not equal: make them equal by shifting the commas and changing the exponents
	// this is done by shifting the bigger value to the left until the exponents are equal, if no more
	// shifting is possible, shift the smaller value to the right until the exponents are equal
	// other._exp is used to store the difference between the exponents as it is not needed anymore
	if (other._exp > _exp) {
		other._exp -= _exp;

		// test if the the bigger value can be shifted enough to the left to compensate the other._experence in exponents
		if (other._exp < DECIMAL_VALUE_PRECISION && std::abs(other._val) < powers_of_ten[DECIMAL_VALUE_PRECISION - other._exp]) {
			other._val *= powers_of_ten[other._exp];
		} else {
			// when it can't be shifted enough, shift it as much as possible and shift the smaller value to the right
			uint8_t max_shift = DECIMAL_VALUE_PRECISION - count_digits(other._val);
			other._val *= powers_of_ten[max_shift];
			other._exp -= max_shift;

			if (other._exp > DECIMAL_VALUE_PRECISION) _val = 0;
			else shift_right(_val, other._exp);
			_exp += other._exp;
		}
	} else if (other._exp < _exp) {
		other._exp = _exp - other._exp;

		// test if the the bigger value can be shifted enough to the left to compensate the other._experence in exponents
		if (other._exp < DECIMAL_VALUE_PRECISION && std::abs(_val) < powers_of_ten[DECIMAL_VALUE_PRECISION - other._exp]) {
			_val *= powers_of_ten[other._exp];
			_exp -= other._exp;
		} else {
			// when it can't be shifted enough, shift it as much as possible and shift the smaller value to the right
			uint8_t shift = DECIMAL_VALUE_PRECISION - count_digits(_val);
			_val *= powers_of_ten[shift];
			_exp -= shift;

			other._exp -= shift;
			if (other._exp > DECIMAL_VALUE_PRECISION) other._val = 0;
			else shift_right(other._val, other._exp);
		}
	}

	// assuming the exponents are equal: add the values together
	_val += other._val;

	// exponent can't overflow because it can only be betweeen the exponents of the two values (which are not overflown)
	// value can only overflow to double of DECIMAL_VALUE_MAX -> if overflow, shift the comma by one and increase the exponent by one
	// only possible because int64_t can represent at least double of DECIMAL_VALUE_MAX
	// if exponent is already DECIMAL_EXP_MAX, it is gonna be too big -> Error
	if (std::abs(_val) > DECIMAL_VALUE_MAX) {
		if (_exp == DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
		_exp++;
		shift_right_one(_val);
	}
	return *this;
}

Decimal& Decimal::operator-=(Decimal other)
{
	// add the negative value
	other.negate();
	*this += other;
	return *this;
}

Decimal& Decimal::operator*=(Decimal other)
{
	// a * 10^b * c * 10^d = a * c * 10^(b + d)
	// => multiply values and add exponents
	maximize_exp();
	other.maximize_exp();

	if (_val == 0 || other._val == 0) {
		_val = 0;
		_exp = 0;
		return *this;
	}

	// test if the value can be multiplied without overflow
	int64_t test = _val * other._val;
	if (test / other._val == _val) {
		_val = test;
		_exp += other._exp;

		// value can still be bigger than DECIMAL_VALUE_MAX -> shift the value to the left by one and increase the exponent by one
		if (std::abs(_val) > DECIMAL_VALUE_MAX) {
			_exp++;
			if (std::abs(_exp) > DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
			shift_right_one(_val);
		} else if (std::abs(_exp) > DECIMAL_EXP_MAX) {
			// check how many zeros are before _val (when in base 10)
			uint8_t shift = DECIMAL_VALUE_PRECISION - count_digits(_val);
			// check if, when shifting the value to the left, the exponent would be still too big
			if (_exp > DECIMAL_EXP_MAX + shift) Error::throw_error(Error::ErrorType::MATH_ERROR);
			else {
				shift_right(_val, _exp - DECIMAL_EXP_MAX);
				_exp = DECIMAL_EXP_MAX;
			}
		}
	} else {
		// split each value into two parts so that no part has more than 9 digits => no multiplication between two parts can have more than 18 digits
		int64_t val_lo = _val % powers_of_ten[9];
		_val /= powers_of_ten[9];
		int64_t other_val_lo = other._val % powers_of_ten[9];
		other._val /= powers_of_ten[9];

		// this * other
		// = (val_lo + _val * 10^9) * (other_val_lo + other._val * 10^9)
		// = (val_lo / 10^9 + _val) * (other_val_lo / 10^9 + other._val)    when increasing _exp of the result by 18
		// = (val_lo * other_val_lo / 10^18) + (val_lo * other._val / 10^9) + (_val * other_val_lo / 10^9) + (_val * other._val)
		// = (_val * other._val) + ((_val * other_val_lo + val_lo * other._val) / 10^9) + (val_lo * other_val_lo / 10^18)
		// = (_val * other._val * 10^shift) + ((_val * other_val_lo + val_lo * other._val) * 10^(shift - 9)) + (val_lo * other_val_lo / 10^(18 - shift))   when decreasing _exp of the result by shift
		// the result of the first multiplication is shifted to the left as much as possible for maximum precision, shift is the number of digits it was shifted

		uint8_t shift;
		int8_t last_digit = 0;
		int64_t part_res;
		// _val * other._val * 10^shift
		int64_t res = _val * other._val;
		// (_val * other_val_lo + val_lo * other._val) / 10^(9 - shift)
		if (res == 0) {
			res = val_lo * other._val + _val * other_val_lo;
			shift = DECIMAL_VALUE_PRECISION - count_digits(res);
			res *= powers_of_ten[shift];
			shift += 9;
		} else {
			shift = DECIMAL_VALUE_PRECISION - count_digits(res);
			res *= powers_of_ten[shift];
			if (shift >= 9) res += (val_lo * other._val + _val * other_val_lo) * powers_of_ten[shift - 9];
			else {
				part_res = val_lo * other._val + _val * other_val_lo;
				part_res /= powers_of_ten[8 - shift];
				last_digit = part_res % 10;
				res += part_res / 10;
			}
		}
		// val_lo * other_val_lo / 10^(18 - shift)
		part_res = val_lo * other_val_lo;
		part_res /= powers_of_ten[17 - shift];
		last_digit += part_res % 10;
		res += part_res / 10;

		// round the last digit, note that it can have more than one digit
		res += last_digit / 10;
		last_digit %= 10;
		if (last_digit > 4) res += 1;
		else if (last_digit < -4) res -= 1;

		_val = res;
		_exp += 18 + other._exp - shift;

		// exp can't be decreased anymore because all digits of _val are occupied => Error when Exponent is too big
		if (std::abs(_exp) > DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::MATH_ERROR);
	}

	return *this;
}

Decimal& Decimal::operator/=(Decimal other)
{
	if (other._val == 0) {
		Error::throw_error(Error::ErrorType::MATH_ERROR);
		return *this;
	}

	// if other._val has more than 17 digits, the code below could get stuck in an infinite loop as the result of the division could be 0
	if (other._val >= powers_of_ten[17]) {
		shift_right_one(other._val);
		other._exp++;
	}

	// res stores the result, every step it is shifted to the left, until all 18 digits are occupied
	int64_t res = _val / other._val;
	_val %= other._val;
	if (_val != 0) {
		while (true) {
			// shift the remainder _val to the left as much as possible and store the amount of digits it was shifted
			uint8_t shift = DECIMAL_VALUE_PRECISION - count_digits(_val);
			_val *= powers_of_ten[shift];
			// divide the shifted remainder _val by the other value and add the result to div, set _val to the remainder
			int64_t div = _val / other._val;
			_val %= other._val;
			// try shifting the result to the left by shift, if it is not possible, shift it as much as possible and break the loop
			uint8_t max_shift = DECIMAL_VALUE_PRECISION - count_digits(res);
			if (shift > max_shift) {
				shift_right(div, shift - max_shift);
				res *= powers_of_ten[max_shift];
				res += div;
				_exp -= max_shift;
				break;
			}
			// if shift is not too big, shift the result to the left by shift and add div
			res *= powers_of_ten[shift];
			res += div;
			// decrease the exponent by shift
			_exp -= shift;
			// if the remainder is zero, the result is exact, break the loop
			if (_val == 0) break;
		}
	}

	// set _val to the result and increase the exponent by the exponent of the other value because
	// a * 10^b / c * 10^d = a / c * 10^(b - d)
	_val = res;
	_exp -= other._exp;

	return *this;
}

Decimal& Decimal::operator%=(Decimal other)
{
	maximize_exp();
	other.maximize_exp();
	if (_val == other._val && _exp == other._exp) {
		_val = 0;
		_exp = 0;
		return *this;
	}

	// make the exponents equal, if digits would be lost, mod does not make sense => Error
	if (other._exp > _exp) {
		other._exp -= _exp;
		if (other._exp < DECIMAL_VALUE_PRECISION && std::abs(other._val) < powers_of_ten[DECIMAL_VALUE_PRECISION - other._exp]) {
			other._val *= powers_of_ten[other._exp];
		} else Error::throw_error(Error::ErrorType::MATH_ERROR);
	} else if (other._exp < _exp) {
		other._exp = _exp - other._exp;
		if (other._exp < DECIMAL_VALUE_PRECISION && std::abs(_val) < powers_of_ten[DECIMAL_VALUE_PRECISION - other._exp]) {
			_val *= powers_of_ten[other._exp];
			_exp -= other._exp;
		} else Error::throw_error(Error::ErrorType::MATH_ERROR);
	}

	_val %= other._val;
	return *this;
}

Decimal& Decimal::operator^=(Decimal other)
{
	ln();
	operator*=(other);
	exp();
	shift_right(_val, 2);
	_exp += 2;
	return *this;
}

Decimal& Decimal::ln()
{
	// TODO: make this slightly bigger than 1
	// https://math.stackexchange.com/questions/977586/is-there-an-approximation-to-the-natural-log-function-at-large-values/977836#977836
	if (_val <= 0) {
		std::cout << "Error: Logarithm of a negative number" << std::endl;
		return *this;
	}

	// TODO: store error (Khan sum)

	uint8_t exp = count_digits(_val) - 1;
	Decimal y = Decimal(_val - powers_of_ten[exp]) / Decimal(_val + powers_of_ten[exp]);
	exp += _exp;
	Decimal top = y;
	operator=(y);
	y *= y;

	for (uint8_t i = 3; add_changed((top *= y) / i); i += 2) {}
	operator*=(2);
	operator+=(Decimal(exp) * LN10);
	return *this;
}

Decimal& Decimal::log(Decimal other)
{
	ln();
	other.ln();
	operator/=(other);
	return *this;
}

Decimal& Decimal::exp()
{
	// if value is too big, throw error
	if (operator>(Decimal(234172903957494446, -14))) {
		std::cout << "Error: Decimal overflow" << std::endl;
		return *this;
	}
	// TODO: store error (Khan sum)

	// wolfram alpha:
	// e^(a 10^b) = sum_(k=0)^(infinity) (10^b a)^k/(k!)
	Decimal fact = 1;
	Decimal mult = *this;
	Decimal denom = 1;
	_val = 1;
	_exp = 0;

	for (uint16_t i = 1; add_changed((denom *= mult) / (fact *= i)); i++) {}
	return *this;
}

Decimal& Decimal::sqrt()
{
	// TODO: optimize
	operator^=(Decimal(5, -1));
	return *this;
}

Decimal& Decimal::root(Decimal other)
{
	operator^=(Decimal(1) / other);
	return *this;
}

Decimal& Decimal::factorial()
{
	maximize_exp();
	if (_exp > 3 || _val < 0 || (_val *= powers_of_ten[_exp]) > 3253) Error::throw_error(Error::ErrorType::MATH_ERROR);
	else {
		Decimal res = _val;
		_val = 1;
		_exp = 0;
		for (; res._val > 1; res._val--)
			operator*=(res);
	}
	return *this;
}


Decimal& Decimal::sin()
{
	return *this;
}

Decimal& Decimal::cos()
{
	operator+=(90);
	sin();
	return *this;
}

Decimal& Decimal::tan()
{
	return *this;
}

Decimal& Decimal::asin()
{
	return *this;
}

Decimal& Decimal::acos()
{
	return *this;
}

Decimal& Decimal::atan()
{
	return *this;
}

Decimal& Decimal::sinh()
{
	return *this;
}

Decimal& Decimal::cosh()
{
	return *this;
}

Decimal& Decimal::tanh()
{
	return *this;
}

Decimal& Decimal::asinh()
{
	return *this;
}

Decimal& Decimal::acosh()
{
	return *this;
}

Decimal& Decimal::atanh()
{
	return *this;
}

Decimal& Decimal::round()
{
	if (_exp < 0) {
		if (_exp > DECIMAL_VALUE_PRECISION) {
			_val = 0;
			_exp = 0;
		} else {
			shift_right(_val, -_exp);
			_exp = 0;
		}
	}
	return *this;
}

Decimal& Decimal::floor()
{
	if (_exp < 0) {
		if (-_exp > DECIMAL_VALUE_PRECISION) {
			_val = 0;
			_exp = 0;
		} else {
			_val /= powers_of_ten[-_exp];
			if (_val < 0) _val--;
			_exp = 0;
		}
	}
	return *this;
}

Decimal& Decimal::ceil()
{
	if (_exp < 0) {
		if (-_exp > DECIMAL_VALUE_PRECISION) {
			_val = 0;
			_exp = 0;
		} else {
			_val /= powers_of_ten[-_exp];
			if (_val > 0) _val++;
			_exp = 0;
		}
	}
	return *this;
}

Decimal& Decimal::to_int()
{
	if (_exp < 0) {
		if (-_exp > DECIMAL_VALUE_PRECISION) {
			_val = 0;
			_exp = 0;
		} else {
			_val /= powers_of_ten[-_exp];
			_exp = 0;
		}
	}
	return *this;
}

Decimal& Decimal::abs()
{
	_val = std::abs(_val);
	return *this;
}

Decimal& Decimal::negate()
{
	_val *= -1;
	return *this;
}

Decimal& Decimal::ran()
{
	// TODO: more digits
	_exp = -3;
	_val = Utils::us_since_boot() % 1000;
	return *this;
}

Decimal& Decimal::ran_int(Decimal end)
{
	// TODO
	return *this;
}

Decimal& Decimal::pol(Decimal other)
{
	// TODO
	return *this;
}

Decimal& Decimal::rec(Decimal other)
{
	// TODO
	return *this;
}

Decimal& Decimal::gcd(Decimal other)
{
	// TODO
	return *this;
}

Decimal& Decimal::lcm(Decimal other)
{
	// TODO
	return *this;
}

void Decimal::value_to_key_set(KEY_SET& res) const
{
	if (_val == 0) {
		res.push_back(48);
		return;
	}
	int64_t val_copy = std::abs(_val);
	uint8_t size = res.size();
	while (val_copy != 0) {
		res.push_back((KEY)(val_copy % 10) + 48);
		val_copy /= 10;
	}
	std::reverse(res.begin() + size, res.end());
}

void Decimal::exp_to_key_set(KEY_SET& res) const
{
	if (_exp == 0) {
		res.push_back(48);
		return;
	}
	int64_t exp_copy = std::abs(_exp);
	auto begin = res.end();
	while (exp_copy != 0) {
		res.push_back((KEY)(exp_copy % 10) + 48);
		exp_copy /= 10;
	}
	std::reverse(begin, res.end());
}

KEY_SET Decimal::to_key_set(uint8_t max_size) const
{
	// TODO: test if fixed
	KEY_SET res;
	res.reserve(max_size);
	maximize_exp();
	if (_val < 0) max_size--;
	uint8_t digits = count_digits(_val);
	// number of digits that would be lost if it was converted without scientific notation
	int16_t missing_digits = digits > -_exp ? (digits >= max_size ? digits - max_size + 1 : 0) : -_exp - max_size + 2;

	if (_exp >= 0 && _exp + digits <= max_size) {
		// no comma needed
		if (_val < 0) res.push_back(KEY_NEGATE);
		value_to_key_set(res);
		for (uint8_t i = 0; i < _exp; i++) res.push_back('0');
	} else if (_exp < 0 && missing_digits <= exp_count_digits() + (_exp < 0) + 3) {
		if (missing_digits > 0) {
			shift_right(_val, missing_digits);
			_exp += missing_digits;
			digits -= missing_digits;
		}
		// comma needed
		if (-_exp < digits) {
			int64_t val_copy = std::abs(_val);
			for (uint8_t i = 0; i < -_exp; i++) {
				res.push_back((KEY)(val_copy % 10) + 48);
				val_copy /= 10;
			}
			res.push_back(44);
			while (val_copy != 0) {
				res.push_back((KEY)(val_copy % 10) + 48);
				val_copy /= 10;
			}
		} else {
			int64_t val_copy = std::abs(_val);
			while (val_copy != 0) {
				res.push_back((KEY)(val_copy % 10) + 48);
				val_copy /= 10;
			}
			for (uint8_t i = res.size(); i < -_exp; i++) res.push_back(48);
			res.push_back(',');
			res.push_back('0');
		}
		if (_val < 0) res.push_back(KEY_NEGATE);
		std::reverse(res.begin(), res.end());
	} else {
		// decimal can't be represented without scientific notation while satisfying the max_size
		_exp += digits - 1;
		if (_exp == 0) res.push_back('0');
		else {
			int64_t exp_copy = std::abs(_exp);
			while (exp_copy != 0) {
				res.push_back((KEY)(exp_copy % 10) + 48);
				exp_copy /= 10;
			}
			if (_exp < 0) res.push_back(KEY_NEGATE);
		}
		res.push_back(KEY_SCIENTIFIC_E);
		max_size -= res.size() + 2;

		if (digits > max_size) shift_right(_val, digits - max_size);
		if (_val < 10) res.push_back((KEY)_val + 48);
		else {
			int64_t val_copy = std::abs(_val);
			while (val_copy != 0) {
				res.push_back((KEY)(val_copy % 10) + 48);
				val_copy /= 10;
			}
			res.insert(res.end() - 1, ',');
		}
		if (_val < 0) res.push_back(KEY_NEGATE);
		std::reverse(res.begin(), res.end());
	}

	return res;
}

void Decimal::maximize_exp() const
{
	if (_val == 0) {
		_exp = 0;
		return;
	}
	while (_val % 10 == 0) {
		_val /= 10;
		_exp++;
	}
}

bool Decimal::add_changed(Decimal other)
{
	if (_val == 0) {
		_val = other._val;
		_exp = other._exp;
		return true;
	}
	if (other._val == 0) return false;

	if (other._exp > _exp) {
		other._exp -= _exp;
		if (other._exp < DECIMAL_VALUE_PRECISION && std::abs(other._val) < powers_of_ten[DECIMAL_VALUE_PRECISION - other._exp]) {
			other._val *= powers_of_ten[other._exp];
		} else {
			uint8_t max_shift = DECIMAL_VALUE_PRECISION - count_digits(other._val);
			other._val *= powers_of_ten[max_shift];
			other._exp -= max_shift;

			if (other._exp > DECIMAL_VALUE_PRECISION) _val = 0;
			else shift_right(_val, other._exp);
			_exp += other._exp;
		}
	} else if (other._exp < _exp) {
		other._exp = _exp - other._exp;
		if (other._exp < DECIMAL_VALUE_PRECISION && std::abs(_val) < powers_of_ten[DECIMAL_VALUE_PRECISION - other._exp]) {
			_val *= powers_of_ten[other._exp];
			_exp -= other._exp;
		} else {
			uint8_t shift = DECIMAL_VALUE_PRECISION - count_digits(_val);
			_val *= powers_of_ten[shift];
			_exp -= shift;

			other._exp -= shift;
			if (other._exp > DECIMAL_VALUE_PRECISION) return false;
			else shift_right(other._val, other._exp);
		}
	}
	_val += other._val;
	if (std::abs(_val) > DECIMAL_VALUE_MAX) {
		if (_exp == DECIMAL_EXP_MAX) std::cout << "Error: Decimal overflow" << std::endl;
		_exp++;
		shift_right_one(_val);
	}
	return true;
}

uint8_t Decimal::exp_count_digits() const
{
	int16_t exp_abs = std::abs(_exp);
	if (exp_abs > powers_of_ten[2]) {
		if (exp_abs == 0) return 0;
		if (exp_abs < powers_of_ten[1]) return 1;
		else return 2;
	} else {
		if (exp_abs < powers_of_ten[3]) return 3;
		if (exp_abs < powers_of_ten[4]) return 4;
		else return 5;
	}
}

void Decimal::shift_right(int64_t& value, uint8_t shift)
{
	value /= powers_of_ten[shift - 1];
	int8_t last_digit = value % 10;
	if (last_digit > 4) value += 10;
	else if (last_digit < -4) value -= 10;
	value /= 10;
}

void Decimal::shift_right(uint64_t& value, uint8_t shift)
{
	value /= powers_of_ten[shift - 1];
	if (value % 10 > 4) value += 10;
	value /= 10;
}

void Decimal::shift_right_one(int64_t& value)
{
	int8_t last_digit = value % 10;
	value /= 10;
	if (last_digit > 4) value += 1;
	else if (last_digit < -4) value -= 1;
}

uint8_t Decimal::count_digits(int64_t value)
{
	return count_digits_unsigned(std::abs(value));
}

uint8_t Decimal::count_digits_unsigned(uint64_t value)
{
	if (value < powers_of_ten[10]) {
		if (value < powers_of_ten[5]) {
			if (value < powers_of_ten[2]) {
				if (value == 0) return 0;
				if (value < powers_of_ten[1]) return 1;
				else return 2;
			} else {
				if (value < powers_of_ten[3]) return 3;
				if (value < powers_of_ten[4]) return 4;
				else return 5;
			}
		} else {
			if (value < powers_of_ten[7]) {
				if (value < powers_of_ten[6]) return 6;
				else return 7;
			} else {
				if (value < powers_of_ten[8]) return 8;
				if (value < powers_of_ten[9]) return 9;
				else return 10;
			}
		}
	} else {
		if (value < powers_of_ten[15]) {
			if (value < powers_of_ten[12]) {
				if (value < powers_of_ten[11]) return 11;
				else return 12;
			} else {
				if (value < powers_of_ten[13]) return 13;
				if (value < powers_of_ten[14]) return 14;
				else return 15;
			}
		} else {
			if (value < powers_of_ten[17]) {
				if (value < powers_of_ten[16]) return 16;
				else return 17;
			} else {
				if (value < powers_of_ten[18]) return 18;
				else return 19;
			}
		}
	}
}