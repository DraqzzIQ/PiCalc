#pragma once
#include "constant/Chars.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "datastructs/Bitset2D.h"
#include "datastructs/Decimal.h"
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
	Number(int64_t value, int16_t exp);
	/// <summary>
	/// create a Number by copying another
	/// </summary>
	Number(const Number* other);
	/// <summary>
	/// create a Number from a Decimal
	/// </summary>
	/// <param name="value"></param>
	Number(Decimal value);
	/// <summary>
	/// destroy the Number and clear allocated Memory
	/// </summary>
	~Number();
	/// <summary>
	/// copy other to this
	/// </summary>
	Number* operator=(const Number* other);

	/// <summary>
	/// add other to this
	/// IMPORTANT: does not clone => other is deleted after this operation
	/// </summary>
	Number* add(Number* other);
	/// <summary>
	/// subtract other from this
	/// IMPORTANT: does not clone => other is deleted after this operation
	/// </summary>
	Number* subtract(Number* other);
	/// <summary>
	/// multiply this with other
	/// IMPORTANT: does not clone => other is deleted after this operation
	/// </summary>
	Number* multiply(Number* other);
	/// <summary>
	/// divide this by other
	/// IMPORTANT: does not clone => other is deleted after this operation
	/// </summary>
	Number* divide(Number* other);
	/// <summary>
	/// calculate the remainder of this divided by other
	/// IMPORTANT: does not clone => other is deleted after this operation
	/// </summary>
	Number* mod(Number* other);

	/// <summary>
	/// natural logarithm of this
	/// </summary>
	Number* ln();
	/// <summary>
	/// logarithm base 10 of this
	/// </summary>
	Number* log();
	/// <summary>
	/// logarithm base other of this
	/// </summary>
	Number* log(Number* other);
	/// <summary>
	/// raises e to the power of this
	/// </summary>
	Number* exp();
	/// <summary>
	/// raises 10 to the power of this
	/// </summary>
	Number* pow10();
	/// <summary>
	/// raises this to the power of other
	/// </summary>
	Number* pow(Number* other);
	/// <summary>
	/// calculates the square root of this
	/// </summary>
	Number* sqrt();
	/// <summary>
	/// calculates the other root of this
	/// </summary>
	Number* root(Number* other);
	/// <summary>
	/// calculates the factorial of this
	/// </summary>
	Number* factorial();

	/// <summary>
	/// sin of this
	/// </summary>
	Number* sin();
	/// <summary>
	/// cos of this
	/// </summary>
	Number* cos();
	/// <summary>
	/// tan of this
	/// </summary>
	Number* tan();
	/// <summary>
	/// asin of this
	/// </summary>
	Number* asin();
	/// <summary>
	/// acos of this
	/// </summary>
	Number* acos();
	/// <summary>
	/// atan of this
	/// </summary>
	Number* atan();
	/// <summary>
	/// sinh of this
	/// </summary>
	Number* sinh();
	/// <summary>
	/// cosh of this
	/// </summary>
	Number* cosh();
	/// <summary>
	/// tanh of this
	/// </summary>
	Number* tanh();
	/// <summary>
	/// asinh of this
	/// </summary>
	Number* asinh();
	/// <summary>
	/// acosh of this
	/// </summary>
	Number* acosh();
	/// <summary>
	/// atanh of this
	/// </summary>
	Number* atanh();

	/// <summary>
	/// round this to the nearest integer
	/// </summary>
	Number* round();
	/// <summary>
	/// round this down to the nearest integer
	/// </summary>
	Number* floor();
	/// <summary>
	/// round this up to the nearest integer
	/// </summary>
	Number* ceil();
	/// <summary>
	/// absolute value of this
	/// </summary>
	Number* abs();
	/// <summary>
	/// cuts off the decimal part of this
	/// </summary>
	Number* to_int();
	/// <summary>
	/// changes the sign of this
	/// </summary>
	Number* negate();
	/// <summary>
	/// divides this by 100
	/// </summary>
	Number* percent();

	/// <summary>
	/// rectangular to polar coordinates (this = x, other = y)
	/// </summary>
	Number* pol(Number* other);
	/// <summary>
	/// polar to rectangular coordinates (this = r, other = theta)
	/// </summary>
	Number* rec(Number* other);
	/// <summary>
	/// greatest common divisor
	/// </summary>
	Number* gcd(Number* other);
	/// <summary>
	/// least common multiple
	/// </summary>
	Number* lcm(Number* other);
	/// <summary>
	/// random integer between this and other (both inclusive)
	/// </summary>
	Number* ran_int(Number* other);

	/// <summary>
	/// simplyfiy this as much as possible without losing any precision
	/// </summary>
	void simplify();
	/// <summary>
	/// return a single decimal representing this (often looses precision)
	/// </summary>
	Decimal to_value() const;
	/// <summary>
	/// returns all possible representations of this as a KEY_SET
	/// </summary>
	std::vector<KEY_SET> to_key_set() const;

	private:
	/// <summary>
	/// clones this number without cloning its children (only adresses of Numbers in children are copied)
	/// </summary>
	Number* clone() const;
	/// <summary>
	/// clone this Number recursively
	/// </summary>
	Number* deep_clone() const;

	Decimal _value;
	std::vector<Number*> _children;
};
