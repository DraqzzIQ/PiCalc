#include "NumberParser.h"

NumberParser::NumberParser()
{
	_val = 0;
	_exp = 0;
	_state = 0;
	_value_cnt = 0;
}

NumberParser::~NumberParser() {}

void NumberParser::clear_number()
{
	_val = 0;
	_exp = 0;
	_state = 0;
	_value_cnt = 0;
}

bool NumberParser::add_digit(const KEY digit)
{
	// TODO: numbers with more than 18 digits
	if (_state & 0b00100000) {
		if (digit < 10) {
			if (std::abs(_val) < Decimal::powers_of_ten[DECIMAL_VALUE_PRECISION - 1]) {
				_exp--;
				if (-_exp == DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				_state++;
				_val = _val * 10 + digit;
			}
		} else if (digit == 238) {
			if (!(_state & 0b00011111)) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			_state ^= 0b00100000;
		} else Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
	} else {
		// periodic digits placed, but periodic inactive
		if (_state & 0b00011111) return false;
		if (digit < 10) { // key is digit
			if (_state & 0b10000000) {
				if (std::abs(_exp) >= Decimal::powers_of_ten[DECIMAL_EXP_PRECISION - 1]) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				else {
					_exp = _exp * 10 + digit;
					_value_cnt |= 0b10000000;
				}
			} else if (_state & 0b01000000) {
				if (std ::abs(_val) < Decimal::powers_of_ten[DECIMAL_VALUE_PRECISION - 1]) {
					_exp--;
					if (-_exp == DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
					_val = _val * 10 + digit;
				}
			} else {
				if (std ::abs(_val) < Decimal::powers_of_ten[DECIMAL_VALUE_PRECISION - 1]) {
					_val = _val * 10 + digit;
				} else {
					_exp++;
					if (_exp == DECIMAL_EXP_MAX) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
				}
			}
		} else if (digit == 69) {                 // key is +
			if (!(_state & 0b10000000) || _value_cnt & 0b10000000) return false;
		} else if (digit == 70 || digit == 116) { // key is -
			if (_state & 0b10000000 && !(_value_cnt & 0b10000000)) _value_cnt ^= 0b01000000;
			else return false;
		} else if (digit == 82) { // key is comma
			if (_state & 0b11000000) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			_state |= 0b01000000;
		} else if (digit == 127) { // key is exp
			if (_state & 0b10000000) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			_state |= 0b10000000;
		} else if (digit == 133) { // key is periodic
			if (!(_state & 0b01000000) || _state & 0b10000000) Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
			else _state |= 0b00100000;
		} else {
			return false;
		}
	}
	_value_cnt++;
	return true;
}

uint8_t NumberParser::get_value_cnt()
{
	return _value_cnt & 0b00111111;
}

Number* NumberParser::get_number()
{
	Number* num;
	if (_value_cnt & 0b01000000) _exp = -_exp;
	if (_value_cnt == 0) {
		Error::throw_error(Error::ErrorType::SYNTAX_ERROR);
		num = new Number();
	} else if (_state & 0b00011111) {
		num = new Number(_val, _exp, _state & 0b00011111);
	} else {
		num = new Number(_val, _exp);
	}

	clear_number();
	return num;
}