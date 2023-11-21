#pragma once
#include "constant/Chars.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "datastructs/Bitset2D.h"
#include <cmath>
#include <string>
#include <vector>


class Number
{
	public:
	Number();
	Number(const uint64_t value, const uint16_t exp);
	Number(const Number& other);
	~Number();

	Number operator+(const Number& other);
	Number operator-(const Number& other);
	Number operator*(const Number& other);
	Number operator/(const Number& other);
	Number operator%(const Number& other);
	Number operator^(const Number& other);

	Number operator+(const double& other);
	Number operator-(const double& other);
	Number operator*(const double& other);
	Number operator/(const double& other);
	Number operator%(const double& other);
	Number operator^(const double& other);

	Number operator-();

	Number& operator+=(const Number& other);
	Number& operator-=(const Number& other);
	Number& operator*=(const Number& other);
	Number& operator/=(const Number& other);
	Number& operator%=(const Number& other);
	Number& operator^=(const Number& other);
	Number& operator=(const Number& other);

	Number& operator+=(const double& other);
	Number& operator-=(const double& other);
	Number& operator*=(const double& other);
	Number& operator/=(const double& other);
	Number& operator%=(const double& other);
	Number& operator^=(const double& other);
	Number& operator=(const double& other);

	Number& log();
	Number& log(const double& other);
	Number& log(const Number& other);
	Number& ln();

	Number& sin();
	Number& cos();
	Number& tan();
	Number& asin();
	Number& acos();
	Number& atan();
	Number& sinh();
	Number& cosh();
	Number& tanh();
	Number& asinh();
	Number& acosh();
	Number& atanh();

	Number& round();
	Number& floor();
	Number& ceil();
	Number& abs();
	Number& to_int();
	Number& negate();

	Number& pow(const Number& other);
	Number& pow(const double& other);
	Number& factorial();

	Number& sqrt();
	Number& root(const Number& other);
	Number& root(const double& other);

	static Number pol(const Number& first, const Number& second);
	static Number rec(const Number& first, const Number& second);
	static Number gcd(const Number& first, const Number& second);
	static Number lcm(const Number& first, const Number& second);
	static Number ran_int(const Number& first, const Number& second);

	double get_value() const;
	bool add_digit(const uint8_t digit);
	uint16_t finalize();
	Bitset2D render() const;

	private:
	struct NumberNode {
		Decimal value;

		uint8_t operation = 0;
		NumberNode* first = nullptr;
		NumberNode* second = nullptr;

		~NumberNode()
		{
			if (first != nullptr) delete first;
			if (second != nullptr) delete second;
		}

		NumberNode* clone()
		{
			if (this) return new NumberNode{ value, exp, operation, first->clone(), second->clone() };
			else return nullptr;
		}
	};
	NumberNode* _root;

	uint8_t _state = 0;
	uint16_t _periodic = 0;
	uint16_t _value_cnt = 0;
};
