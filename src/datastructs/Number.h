#pragma once
#include "constant/Constants.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
#include "datastructs/Bitset2D.h"
#include "datastructs/Decimal.h"
#include "utils/Utils.h"

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
	/// create a Number with given value, exponent and number of periodic digits
	/// </summary>
	Number(int64_t value, int16_t exp, uint8_t periodic);
	/// <summary>
	/// create a Number by copying another<para/>
	/// IMPORTANT: Number(0) results in an error as 0 is interpreted as nullptr
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
	/// swaps this and other
	/// </summary>
	// Number* swap(Number* other);
	/// <summary>
	/// create a Number from a KEY
	/// </summary>
	static Number* from_key(KEY key);
	/// <summary>
	/// random Number between 0 and 1, 3 digits precision
	/// </summary>
	/// <returns></returns>
	static Number* ran();

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
	/// logarithm base other of this
	/// </summary>
	Number* log(Number* other);
	/// <summary>
	/// raises e to the power of this
	/// </summary>
	Number* exp();
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
	/// converts this Number from mode to degrees, where 0 = degrees, 1 = radians, 2 = gradians
	/// </summary>
	Number* from_angle(uint8_t mode);
	/// <summary>
	/// converts this Number to mode from degrees, where 0 = degrees, 1 = radians, 2 = gradians
	/// </summary>
	Number* to_angle(uint8_t mode);

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
	/// return a single decimal representing this (often looses precision)
	/// </summary>
	bool to_value();
	/// <summary>
	/// return a decimal representing this while replacing all variables with their corresponding values
	/// </summary>
	/// <param name="variables"></param>
	void to_value(std::map<KEY, Number*>& variables);
	void to_key_set(KEY_SET& result) const;
	/// <summary>
	/// returns all possible representations of this as a KEY_SET
	/// </summary>
	std::vector<KEY_SET> get_all_representations(std::map<KEY, Number*>& variables);

	private:
	/// <summary>
	/// returns whether this contains a variable
	/// </summary>
	/// <returns></returns>
	bool contains_var() const;
	/// <summary>
	/// converts this to a single Decimal, assuming there are no variables, IMPORTANT: this is unusable after this operation
	/// </summary>
	void to_value_no_check();
	/// <summary>
	/// replaces all variables in this with their corresponding values
	/// </summary>
	void replace_variables(std::map<KEY, Number*>& variables);
	/// <summary>
	/// clones this number without cloning its children (only adresses of Numbers in children are copied)
	/// </summary>
	Number* clone() const;
	/// <summary>
	/// clone this Number recursively
	/// </summary>
	Number* deep_clone() const;
	/// <summary>
	/// reduces this number, assumes it is a fraction, else ERROR
	/// </summary>
	void reduce();
	/// <summary>
	/// if this can be converted to a value, return true, else performs this operation on the Number
	/// </summary>
	bool operation_one_val(KEY operation);
	/// <summary>
	/// if this and other can be converted to values, return true, else performs this operation on the Numbers<para/>
	/// IMPORTANT: does not clone => other is unusable after this operation
	/// </summary>
	bool operation_two_val(KEY operation, Number* other);

	/// <summary>
	/// Decimal value of this Number or key if this is not a value
	/// </summary>
	Decimal _value;
	/// <summary>
	/// children if this is a operation
	/// </summary>
	std::vector<Number*> _children;
};
