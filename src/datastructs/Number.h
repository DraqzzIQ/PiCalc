#pragma once
#include "constant/Chars.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "datastructs/Bitset2D.h"
// #include "datastructs/Decimal.h"
#include "calculator/equation.h"
#include <cmath>
#include <string>
#include <vector>

class Number
{
	public:
	/// <summary>
	/// create an empty Number
	/// </summary>
	Number();
	/// <summary>
	/// create a Number with given value and exponent
	/// </summary>
	Number(const int64_t value, const int16_t exp);
	/// <summary>
	/// create a Number by copying another
	/// </summary>
	Number(const Number& other);
	/// <summary>
	/// create a Number from a Decimal
	/// </summary>
	/// <param name="value"></param>
	// Number(const Decimal value);
	/// <summary>
	/// destroy the Number and  clear allocated Memory
	/// </summary>
	~Number();

	/// <summary>
	/// add other to this
	/// </summary>
	Number& operator+=(Number& other);
	/// <summary>
	/// subtract other from this
	/// </summary>
	Number& operator-=(Number& other);
	/// <summary>
	/// multiply this with other
	/// </summary>
	Number& operator*=(Number& other);
	/// <summary>
	/// divide this by other
	/// </summary>
	Number& operator/=(Number& other);
	/// <summary>
	/// calculate the remainder of this divided by other
	/// </summary>
	Number& operator%=(Number& other);
	/// <summary>
	/// raise this to the power of other
	/// </summary>
	Number& operator^=(Number& other);
	/// <summary>
	/// copy other to this
	/// </summary>
	Number& operator=(const Number& other);

	/// <summary>
	/// logarithm base 10 of this
	/// </summary>
	Number& log();
	/// <summary>
	/// logarithm base other of this
	/// </summary>
	Number& log(const Number& other);
	/// <summary>
	/// natural logarithm of this
	/// </summary>
	Number& ln();

	/// <summary>
	/// sin of this
	/// </summary>
	Number& sin();
	/// <summary>
	/// cos of this
	/// </summary>
	Number& cos();
	/// <summary>
	/// tan of this
	/// </summary>
	Number& tan();
	/// <summary>
	/// asin of this
	/// </summary>
	Number& asin();
	/// <summary>
	/// acos of this
	/// </summary>
	Number& acos();
	/// <summary>
	/// atan of this
	/// </summary>
	Number& atan();
	/// <summary>
	/// sinh of this
	/// </summary>
	Number& sinh();
	/// <summary>
	/// cosh of this
	/// </summary>
	Number& cosh();
	/// <summary>
	/// tanh of this
	/// </summary>
	Number& tanh();
	/// <summary>
	/// asinh of this
	/// </summary>
	Number& asinh();
	/// <summary>
	/// acosh of this
	/// </summary>
	Number& acosh();
	/// <summary>
	/// atanh of this
	/// </summary>
	Number& atanh();

	/// <summary>
	/// round this to the nearest integer
	/// </summary>
	Number& round();
	/// <summary>
	/// round this down to the nearest integer
	/// </summary>
	Number& floor();
	/// <summary>
	/// round this up to the nearest integer
	/// </summary>
	Number& ceil();
	/// <summary>
	/// absolute value of this
	/// </summary>
	Number& abs();
	/// <summary>
	/// cuts off the decimal part of this
	/// </summary>
	Number& to_int();
	/// <summary>
	/// changes the sign of this
	/// </summary>
	Number& negate();

	/// <summary>
	/// raises this to the power of other
	/// </summary>
	Number& pow(const Number& other);
	/// <summary>
	/// calculates the factorial of this
	/// </summary>
	Number& factorial();

	/// <summary>
	/// calculates the other root of this
	/// </summary>
	Number& root(const Number& other);

	/// <summary>
	/// rectangulat to polar coordinates
	/// </summary>
	static Number pol(const Number& first, const Number& second);
	/// <summary>
	/// polar to rectangular coordinates
	/// </summary>
	static Number rec(const Number& first, const Number& second);
	/// <summary>
	/// greatest common divisor
	/// </summary>
	static Number gcd(const Number& first, const Number& second);
	/// <summary>
	/// least common multiple
	/// </summary>
	static Number lcm(const Number& first, const Number& second);
	/// <summary>
	/// random integer between first and second (both inclusive)
	/// </summary>
	static Number ran_int(const Number& first, const Number& second);

	/// <summary>
	/// simplyfiy this as much as possible without losing any precision
	/// </summary>
	void simplify();
	/// <summary>
	/// return a single decimal representing this (often looses precision)
	/// </summary>
	double to_value() const;
	/// <summary>
	/// returns all possible representations of this as a KEY_SET
	/// </summary>
	std::vector<KEY_SET> to_key_set() const;

	private:
	struct NumberNode {
		double value;
		KEY operation;
		std::vector<NumberNode*> children;

		/// <summary>
		/// delete this NumberNode recursively
		/// </summary>
		~NumberNode()
		{
			for (NumberNode* child : children) delete child;
		}

		/// <summary>
		/// clone this NumberNode recursively
		/// </summary>
		NumberNode* clone()
		{
			if (this) {
				NumberNode* clone = new NumberNode{ value, operation, {} };
				for (NumberNode* child : children) clone->children.push_back(child->clone());
				return clone;
			} else return nullptr;
		}
	};
	NumberNode* _root;
};
