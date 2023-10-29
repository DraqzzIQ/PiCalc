#pragma once
#include "constant/Chars.h"
#include "constant/Graphics.h"
#include "datastructs/Bitset2D.h"
#include <string>
#include <vector>


class Number
{
	public:
	Number();
	Number(const double value);
	Number(const std::string value);
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
	Bitset2D render() const;

	private:
	struct NumberNode {
		double value = 0;
		NumberNode* first = nullptr;
		NumberNode* second = nullptr;

		~NumberNode()
		{
			if (first != nullptr) delete first;
			if (second != nullptr) delete second;
		}
	};

	NumberNode* _root;

	double _rounded;
};
