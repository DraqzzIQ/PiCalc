#include "Number.h"

// TODO:
// -output periodic numbers
// -simplify
// -only format Decimal to fraction at the end

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

	_value.set_key(72);
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
	bool is_key = _value.is_key();
	if (!is_key && !other->_value.is_key()) {
		_value += other->_value;
	} else if (is_key && other->_value.is_key()) {
	} else {
		if (is_key && _value.get_key() == 69) {
		} else if (is_key && _value.get_key() == 72) {
		} else if (!is_key && other->_value.get_key() != 69 && other->_value.get_key() != 72) {
			Decimal old_value = _value;
			_value = other->_value;
			other->_value = old_value;
			_children = other->_children;
			other->_children.clear();
		}
	}


	if (!_value.is_key()) {
		if (!other->_value.is_key()) {
			// both are decimal values
			_value += other->_value;
			other = nullptr;
			return this;
		} else {
			// swap this and other so that this is a key and other is a decimal value
			Decimal old_value = _value;
			_value = other->_value;
			other->_value = old_value;
			_children = other->_children;
			other->_children.clear();
		}
	}

	if (other->_value.is_key()) {
		if (other->_value.get_key() == 69) {
			for (Number* child : other->_children) add(child);
		} else {
			_children.push_back(other);
		}
	} else {
		if (_value.get_key() == 69) {
			for (Number* child : _children) {
				if (!child->_value.is_key()) {
					child->_value += other->_value;
					other = nullptr;
					return this;
				} else if (child->_value.get_key() == 72 && !child->_children.at(1)->_value.is_key()) {
					child->_children.at(1)->add(other);
					other = nullptr;
					return this;
				}
			}
			_children.push_back(other);
		} else if (_value.get_key() == 72 && !_children.at(1)->_value.is_key()) {
			_children.at(1)->add(other);
		} else {
			_children.push_back(other);
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
	if (!_value.is_key() && !other->_value.is_key()) {
		_value *= other->_value;
	} else if (_value.get_key() == 71 && other->_value.get_key() == 71) {
		for (Number* child : other->_children) _children.push_back(child);
	} else if (_value.get_key() == 71) {
		_children.push_back(other);
	} else if (other->_value.get_key() == 71) {
		_children = std::vector<Number*>{ clone() };
		for (Number* child : other->_children) _children.push_back(child);
		_value.set_key(71);
	} else {
		_children = std::vector<Number*>{ clone(), other->clone() };
		_value.set_key(71);
	}
	other = nullptr;
	return this;
}

Number* Number::divide(Number* other)
{
	_children = std::vector<Number*>{ clone(), other->clone() };
	_value.set_key(72);
	other = nullptr;
	return this;
}

Number* Number::mod(Number* other)
{
	to_value();
	other->to_value();
	_value %= other->_value;
	delete other;
	return this;
}


Number* Number::ln()
{
	_children = std::vector<Number*>{ Number::from_key(165), clone() };
	_value.set_key(209);
	return this;
}

Number* Number::log()
{
	_children = std::vector<Number*>{ new Number(1, 1), clone() };
	_value.set_key(209);
	return this;
}

Number* Number::log(Number* other)
{
	_children = std::vector<Number*>{ other, clone() };
	_value.set_key(209);
	other = nullptr;
	return this;
}

Number* Number::exp()
{
	_children = std::vector<Number*>{ clone(), Number::from_key(165) };
	_value.set_key(113);
	return this;
}

Number* Number::pow10()
{
	_children = std::vector<Number*>{ clone(), new Number(1, 1) };
	_value.set_key(113);
	return this;
}

Number* Number::pow(Number* other)
{
	_children = std::vector<Number*>{ clone(), other };
	_value.set_key(113);
	other = nullptr;
	return this;
}

Number* Number::sqrt()
{
	_children = std::vector<Number*>{ new Number(2, 0), clone() };
	_value.set_key(134);
	return this;
}

Number* Number::root(Number* other)
{
	_children = std::vector<Number*>{ other, clone() };
	_value.set_key(134);
	other = nullptr;
	return this;
}

Number* Number::factorial()
{
	to_value();
	_value.factorial();
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

Number* Number::from_angle(uint8_t mode)
{
	if (mode == 1) {
		multiply(new Number(180));
		divide(from_key(156));
	} else if (mode == 2) {
		multiply(new Number(9));
		divide(new Number(10));
	}
	return this;
}

Number* Number::to_angle(uint8_t mode)
{
	if (mode == 1) {
		multiply(from_key(156));
		divide(new Number(180));
	} else if (mode == 2) {
		multiply(new Number(10));
		divide(new Number(9));
	}
	return this;
}


Number* Number::round()
{
	to_value();
	_value.round();
	return this;
}

Number* Number::floor()
{
	to_value();
	_value.floor();
	return this;
}

Number* Number::ceil()
{
	to_value();
	_value.ceil();
	return this;
}

Number* Number::abs()
{
	to_value();
	_value.abs();
	return this;
}

Number* Number::to_int()
{
	to_value();
	_value.to_int();
	return this;
}

Number* Number::negate()
{
	if (_value.is_key()) {
		multiply(new Number(-1, 0));
		return this;
	} else {
		_value.negate();
		return this;
	}
}

Number* Number::percent()
{
	divide(new Number(100, 0));
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
	// TODO: simplify and show periodic
	return;
}

bool Number::to_value()
{
	if (contains_key()) return false;
	to_value_no_check();
	return true;
}

void Number::to_value(std::vector<Number*>& variables)
{
	replace_variables(variables);
	to_value_no_check();
}

bool Number::contains_key() const
{
	if (_value.is_key()) return true;
	for (Number* child : _children) {
		if (child->contains_key()) return true;
	}
	return false;
}

void Number::replace_variables(std::vector<Number*>& variables)
{
	if (_value.is_key()) {
		if (_value.get_key() < 69) {
			operator=(variables.at(_value.get_key()));
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
	case 69:
		_value = 0;
		for (Number* child : _children) _value += child->_value;
		break;
	case 71:
		_value = 1;
		for (Number* child : _children) _value *= child->_value;
		break;
	case 72:
		_value = _children[0]->_value;
		_value /= _children[1]->_value;
		break;
	case 85:
		_value = _children[0]->_value.factorial();
		break;
	case 106:
		_value = _children[0]->_value.abs();
		break;
	case 109:
		_value = _children[0]->_value.log(_children[1]->_value);
		break;
	case 111:
		_value = _children[0]->_value.sqrt();
		break;
	case 113:
		_value = _children[0]->_value;
		_value ^= _children[1]->to_value();
		break;
	case 115:
		_value = _children[0]->_value.ln();
		break;
	case 118:
		_value = _children[0]->_value.sin();
		break;
	case 119:
		_value = _children[0]->_value.cos();
		break;
	case 120:
		_value = _children[0]->_value.tan();
		break;
	case 134:
		_value = _children[1]->_value.root(_children[0]->_value);
		break;
	case 135:
		_value.set_value(10, 0);
		_value ^= _children[0]->_value;
		break;
	case 136:
		_value = _children[0]->_value.exp();
		break;
	case 138:
		_value = _children[0]->_value.asin();
		break;
	case 139:
		_value = _children[0]->_value.acos();
		break;
	case 140:
		_value = _children[0]->_value.atan();
		break;
	case 152:
		_value = _children[0]->_value.pol(_children[1]->_value);
		break;
	case 153:
		_value = _children[0]->_value.rec(_children[1]->_value);
		break;
	case 156:
		_value = Decimal::PI;
		break;
	case 160:
		_value = _children[0]->_value.gcd(_children[1]->_value);
		break;
	case 161:
		_value = _children[0]->_value.lcm(_children[1]->_value);
		break;
	case 162:
		_value = _children[0]->_value.to_int();
		break;
	case 163:
		_value = _children[0]->_value.floor();
		break;
	case 164:
		_value = _children[0]->_value.ran_int(_children[1]->_value);
		break;
	case 165:
		_value = Decimal::EULER;
		break;
	case 190:
		_value = _children[0]->_value.sinh();
		break;
	case 191:
		_value = _children[0]->_value.cosh();
		break;
	case 192:
		_value = _children[0]->_value.tanh();
		break;
	case 193:
		_value = _children[0]->_value.asinh();
		break;
	case 194:
		_value = _children[0]->_value.acosh();
		break;
	case 195:
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
		if (key == 69) result.push_back(74);
		if (key == 72) {
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
		if (key == 69) result.back() = 75;
		else if (key != 72) result.pop_back();
	} else {
		KEY_SET val = _value.to_key_set(16);
		result.insert(result.end(), val.begin(), val.end());
	}
}

std::vector<KEY_SET> Number::get_all_representations(std::vector<Number*>& variables)
{
	auto results = std::vector<KEY_SET>();
	simplify();
	if (_value.is_key()) {
		KEY_SET result;
		KEY key = _value.get_key();
		if (key == 72) {
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