#include "Number.h"

// TODO:
// -output periodic numbers
// -simplify
// -only format Decimal to fraction at the end
// -sin/cos/tan

// used KEYs: PLUS, MULTIPLY, DIVIDE, MOD, LOGN (b-th log of a), POWER, ROOTN (b-th root of a), LN, EXP, FACTORIAL, SIN, COS, TAN, ASIN, ACOS, ATAN, SINH, COSH, TANH, ASINH, ACOSH, ATANH, POL, REC, GCD, LCM, TO_INT, FLOOR, CEIL, RAN_INT, EULER, PI

Number::Number()
{
	_value = 0;
	_children = std::vector<Number*>();
}

Number::Number(int64_t value, int16_t exp)
{
	_value.set_value(value, exp);
	_children = std::vector<Number*>();
}

Number::Number(int64_t value, int16_t exp, uint8_t periodic)
{
	exp += periodic;
	value -= value / Decimal::powers_of_ten[periodic];

	_value.set_key(KEY_DIVIDE);
	_children = std::vector<Number*>{
		new Number(value, exp),
		new Number(Decimal::powers_of_ten[periodic] - 1, 0)
	};
}

Number::Number(const Number* other)
{
	operator=(other);
}

Number::Number(Decimal value)
{
	_value = value;
	_children = std::vector<Number*>();
}

Number::~Number()
{
	for (Number* child : _children)
		delete child;
}

Number* Number::operator=(const Number* other)
{
	_value = other->_value;
	_children = std::vector<Number*>();
	for (Number* child : other->_children) _children.push_back(child->deep_clone());
	return this;
}

Number* Number::from_key(KEY key)
{
	Number* number = new Number();
	number->_value.set_key(key);
	return number;
}

Number* Number::ran()
{
	Number* number = new Number();
	number->_value.ran();
	return number;
}

Number* Number::add(Number* other)
{
	KEY this_key = _value.get_key();
	KEY other_key = other->_value.get_key();
	if (!this_key && !other_key) {
		_value += other->_value;
	} else if (this_key && other_key) {
		if (this_key == '+' && !other_key == '+') {
			Decimal old_value = _value;
			_value = other->_value;
			other->_value = old_value;
			std::swap(_children, other->_children);
		}
		// TODO: more cases / rules
		if (other_key == '+') {
			for (Number* child : other->_children) add(child);
		} else {
			_children = std::vector<Number*>{ clone(), other->clone() };
			_value.set_key('+');
		}
	} else {
		if (other_key == '+' || other_key == KEY_DIVIDE) {
			Decimal old_value = _value;
			_value = other->_value;
			other->_value = old_value;
			_children = other->_children;
			other->_children.clear();
		}
		// TODO: more cases / rules
		if (this_key == '+') {
			for (Number* child : _children) {
				if (!child->_value.is_key()) {
					child->_value += other->_value;
					break;
				} else if (child->_value.get_key() == KEY_DIVIDE && !child->contains_var()) {
					child->add(other);
					break;
				}
			}
		} else if (this_key == KEY_DIVIDE) {
			other->multiply(_children.at(1));
			_children.at(0)->add(other);
			reduce();
		} else {
			_children = std::vector<Number*>{ clone(), other->clone() };
			_value.set_key('+');
		}
	}

	other = nullptr;
	return this;
}

Number* Number::subtract(Number* other)
{
	add(other->negate());
	return this;
}

Number* Number::multiply(Number* other)
{
	KEY this_key = _value.get_key();
	KEY other_key = other->_value.get_key();
	if (!this_key && !other_key) {
		_value *= other->_value;
	} else if (this_key && other_key) {
		if (this_key == '+' && !other_key == '+') {
			Decimal old_value = _value;
			_value = other->_value;
			other->_value = old_value;
			std::swap(_children, other->_children);
		}
		// TODO: more cases / rules
		if (other_key == '+') {
			for (Number* child : other->_children) add(child);
		} else {
			_children = std::vector<Number*>{ clone(), other->clone() };
			_value.set_key('+');
		}
	} else {
		if (other_key == KEY_MULTIPLY || other_key == KEY_DIVIDE) {
			Decimal old_value = _value;
			_value = other->_value;
			other->_value = old_value;
			_children = other->_children;
			other->_children.clear();
		}
		// TODO: more cases / rules
		if (this_key == KEY_MULTIPLY) {
			for (Number* child : _children) {
				if (!child->_value.is_key()) {
					child->_value += other->_value;
					break;
				} else if (child->_value.get_key() == KEY_DIVIDE && !child->contains_var()) {
					child->add(other);
					break;
				}
			}
		} else if (this_key == KEY_DIVIDE) {
			other->multiply(_children.at(1));
			_children.at(0)->add(other);
			reduce();
		} else {
			_children = std::vector<Number*>{ clone(), other->clone() };
			_value.set_key('+');
		}
	}
	other = nullptr;
	return this;
}

Number* Number::divide(Number* other)
{
	_children = std::vector<Number*>{ clone(), other->clone() };
	_value.set_key(KEY_DIVIDE);
	other = nullptr;
	return this;
}

Number* Number::mod(Number* other)
{
	if (operation_two_val(KEY_MOD, other)) _value %= other->_value;
	other = nullptr;
	return this;
}


Number* Number::ln()
{
	if (operation_one_val(KEY_LN)) _value.ln();
	return this;
}

Number* Number::log(Number* other)
{
	if (operation_two_val(KEY_LOGN, other)) _value.log(other->_value);
	other = nullptr;
	return this;
}

Number* Number::exp()
{
	if (operation_one_val(KEY_EXP)) _value.exp();
	return this;
}

Number* Number::pow(Number* other)
{
	if (operation_two_val(KEY_POWER, other)) _value ^= other->_value;
	other = nullptr;
	return this;
}

Number* Number::sqrt()
{
	_children = std::vector<Number*>{ new Number(2, 0), clone() };
	_value.set_key(KEY_ROOTN);
	return this;
}

Number* Number::root(Number* other)
{
	_children = std::vector<Number*>{ other, clone() };
	_value.set_key(KEY_ROOTN);
	other = nullptr;
	return this;
}

Number* Number::factorial()
{
	if (operation_one_val('!')) _value.factorial();
	return this;
}


Number* Number::sin()
{
	if (operation_one_val(KEY_SIN)) _value.sin();
	return this;
}

Number* Number::cos()
{
	if (operation_one_val(KEY_COS)) _value.cos();
	return this;
}

Number* Number::tan()
{
	if (operation_one_val(KEY_TAN)) _value.tan();
	return this;
}

Number* Number::asin()
{
	if (operation_one_val(KEY_ASIN)) _value.asin();
	return this;
}

Number* Number::acos()
{
	if (operation_one_val(KEY_ACOS)) _value.acos();
	return this;
}

Number* Number::atan()
{
	if (operation_one_val(KEY_ATAN)) _value.atan();
	return this;
}

Number* Number::sinh()
{
	if (operation_one_val(KEY_SINH)) _value.sinh();
	return this;
}

Number* Number::cosh()
{
	if (operation_one_val(KEY_COSH)) _value.cosh();
	return this;
}

Number* Number::tanh()
{
	if (operation_one_val(KEY_TANH)) _value.tanh();
	return this;
}

Number* Number::asinh()
{
	if (operation_one_val(KEY_ASINH)) _value.asinh();
	return this;
}

Number* Number::acosh()
{
	if (operation_one_val(KEY_ACOSH)) _value.acosh();
	return this;
}

Number* Number::atanh()
{
	if (operation_one_val(KEY_ATANH)) _value.atanh();
	return this;
}


Number* Number::from_angle(uint8_t mode)
{
	if (mode == 1) {
		multiply(new Number(180));
		divide(from_key(KEY_PI));
	} else if (mode == 2) {
		multiply(new Number(9));
		divide(new Number(10));
	}
	return this;
}

Number* Number::to_angle(uint8_t mode)
{
	if (mode == 1) {
		multiply(from_key(KEY_PI));
		divide(new Number(180));
	} else if (mode == 2) {
		multiply(new Number(10));
		divide(new Number(9));
	}
	return this;
}


Number* Number::round()
{
	if (operation_one_val(KEY_RND)) _value.round();
	return this;
}

Number* Number::floor()
{
	if (operation_one_val(KEY_INTG)) _value.floor();
	return this;
}

Number* Number::ceil()
{
	if (operation_one_val(KEY_CEIL)) _value.ceil();
	return this;
}

Number* Number::abs()
{
	if (operation_one_val(KEY_ABS)) _value.abs();
	return this;
}

Number* Number::to_int()
{
	if (operation_one_val(KEY_INT)) _value.to_int();
	return this;
}

Number* Number::negate()
{
	if (_value.is_key()) multiply(new Number(-1));
	else _value.negate();
	return this;
}


Number* Number::pol(Number* other)
{
	if (operation_two_val(KEY_POL, other)) _value.pol(other->_value);
	other = nullptr;
	return this;
}

Number* Number::rec(Number* other)
{
	if (operation_two_val(KEY_REC, other)) _value.rec(other->_value);
	other = nullptr;
	return this;
}

Number* Number::gcd(Number* other)
{
	if (operation_two_val(KEY_GCD, other)) _value.gcd(other->_value);
	other = nullptr;
	return this;
}

Number* Number::lcm(Number* other)
{
	if (operation_two_val(KEY_LCM, other)) _value.lcm(other->_value);
	other = nullptr;
	return this;
}

Number* Number::ran_int(Number* other)
{
	if (operation_two_val(KEY_RAN_INT, other)) _value.ran_int(other->_value);
	other = nullptr;
	return this;
}


void Number::reduce()
{
	// TODO
}

bool Number::operation_one_val(KEY operation)
{
	if (to_value()) return true;
	else {
		_children = std::vector<Number*>{ clone() };
		_value.set_key(operation);
	}
	return false;
}

bool Number::operation_two_val(KEY operation, Number* other)
{
	if (to_value() && other->to_value()) return true;
	else {
		_children = std::vector<Number*>{ clone(), other->clone() };
		_value.set_key(operation);
	}
	return false;
}


bool Number::to_value()
{
	if (contains_var()) return false;
	to_value_no_check();
	return true;
}

void Number::to_value(std::map<KEY, Number*>& variables)
{
	replace_variables(variables);
	to_value_no_check();
}

bool Number::contains_var() const
{
	if (_value.is_key()) return true;
	for (Number* child : _children) {
		if (child->contains_var()) return true;
	}
	return false;
}

void Number::replace_variables(std::map<KEY, Number*>& variables)
{
	if (_value.is_key()) {
		KEY key = _value.get_key();
		if (key > 64 && key < 91 || key > 96 && key < 123) {
			operator=(variables.at(key));
			replace_variables(variables);
		} else {
			for (Number* child : _children) child->replace_variables(variables);
		}
	}
}

void Number::to_value_no_check()
{
	for (Number* child : _children) child->to_value_no_check();
	switch (_value.get_key()) {
	case '+':
		_value = 0;
		for (Number* child : _children) _value += child->_value;
		break;
	case KEY_MULTIPLY:
		_value = 1;
		for (Number* child : _children) _value *= child->_value;
		break;
	case KEY_DIVIDE:
		_value = _children[0]->_value;
		_value /= _children[1]->_value;
		break;
	case '!':
		_value = _children[0]->_value.factorial();
		break;
	case KEY_ABS:
		_value = _children[0]->_value.abs();
		break;
	case KEY_LOGN:
		_value = _children[0]->_value.log(_children[1]->_value);
		break;
	case KEY_SQRT:
		_value = _children[0]->_value.sqrt();
		break;
	case KEY_POWER:
		_value = _children[0]->_value;
		_value ^= _children[1]->_value;
		break;
	case KEY_LN:
		_value = _children[0]->_value.ln();
		break;
	case KEY_SIN:
		_value = _children[0]->_value.sin();
		break;
	case KEY_COS:
		_value = _children[0]->_value.cos();
		break;
	case KEY_TAN:
		_value = _children[0]->_value.tan();
		break;
	case KEY_ROOTN:
		_value = _children[1]->_value.root(_children[0]->_value);
		break;
	case KEY_EXP:
		_value = _children[0]->_value.exp();
		break;
	case KEY_ASIN:
		_value = _children[0]->_value.asin();
		break;
	case KEY_ACOS:
		_value = _children[0]->_value.acos();
		break;
	case KEY_ATAN:
		_value = _children[0]->_value.atan();
		break;
	case KEY_POL:
		_value = _children[0]->_value.pol(_children[1]->_value);
		break;
	case KEY_REC:
		_value = _children[0]->_value.rec(_children[1]->_value);
		break;
	case KEY_PI:
		_value = Decimal::PI;
		break;
	case KEY_GCD:
		_value = _children[0]->_value.gcd(_children[1]->_value);
		break;
	case KEY_LCM:
		_value = _children[0]->_value.lcm(_children[1]->_value);
		break;
	case KEY_INT:
		_value = _children[0]->_value.to_int();
		break;
	case KEY_INTG:
		_value = _children[0]->_value.floor();
		break;
	case KEY_RAN_INT:
		_value = _children[0]->_value.ran_int(_children[1]->_value);
		break;
	case KEY_EULER:
		_value = Decimal::EULER;
		break;
	case KEY_SINH:
		_value = _children[0]->_value.sinh();
		break;
	case KEY_COSH:
		_value = _children[0]->_value.cosh();
		break;
	case KEY_TANH:
		_value = _children[0]->_value.tanh();
		break;
	case KEY_ASINH:
		_value = _children[0]->_value.asinh();
		break;
	case KEY_ACOSH:
		_value = _children[0]->_value.acosh();
		break;
	case KEY_ATANH:
		_value = _children[0]->_value.atanh();
		break;
	}
	for (Number* child : _children) delete child;
	_children.clear();
}

void Number::to_key_set(KEY_SET& result) const
{
	if (_value.is_key()) {
		KEY key = _value.get_key();
		if (key == 43) result.push_back(74);
		if (key == 247) {
			result.push_back(110);
			_children[0]->to_key_set(result);
			result.push_back(237);
			_children[1]->to_key_set(result);
			result.push_back(238);
		} else {
			for (Number* child : _children) {
				child->to_key_set(result);
				result.push_back(_value.get_key());
			}
		}
		if (key == 43) result.back() = 75;
		else if (key != 247) result.pop_back();
	} else {
		KEY_SET val = _value.to_key_set(16);
		result.insert(result.end(), val.begin(), val.end());
	}
}

std::vector<KEY_SET> Number::get_all_representations(std::map<KEY, Number*>& variables)
{
	auto results = std::vector<KEY_SET>();
	if (_value.is_key()) {
		KEY_SET result;
		KEY key = _value.get_key();
		if (key == 247) {
			result.push_back(110);
			_children[0]->to_key_set(result);
			result.push_back(237);
			_children[1]->to_key_set(result);
			result.push_back(238);
		} else {
			for (Number* child : _children) {
				child->to_key_set(result);
				result.push_back(_value.get_key());
			}
		}
		result.pop_back();
		results.push_back(result);
	}

	Number res = *this;
	res.to_value(variables);
	results.push_back(res._value.to_key_set(14));

	return results;
}


Number* Number::clone() const
{
	Number* clone = new Number(_value);
	for (Number* child : _children) clone->_children.push_back(child);
	return clone;
}

Number* Number::deep_clone() const
{
	if (_value.is_key()) {
		Number* clone = new Number();
		clone->_value = _value;
		for (Number* child : _children) clone->_children.push_back(child->deep_clone());
		return clone;
	} else return new Number(_value);
}