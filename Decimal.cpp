#include "Decimal.h"

Decimal::Decimal() {
	_value = 0;
}

Decimal::Decimal(double value) {
	int16_t exp = (value == 0) ? 0 : 1 + (int16_t)std::floor(std::log10(std::fabs(value)));
	_value = (int64_t)(value * std::pow(10, -exp)) << 11;
	_value |= (exp >> 5);
}

Decimal::Decimal(int64_t value, int16_t exp) {
	_value = value << 11;
	_value |= (exp >> 5);
}

Decimal Decimal::operator+(const Decimal& other) {

}