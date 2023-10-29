#pragma once
#include <vector>
#include "constant/Chars.h"
#include "datastructs/Bitset2D.h"


class Number
{
public:
	Number();
	Number(double value);
	Number(int64_t value);
	Number(std::vector<uint8_t> values);
	~Number();

	Number operator+(const Number& other);
	Number operator-(const Number& other);
	Number operator*(const Number& other);
	Number operator/(const Number& other);
	Number operator%(const Number& other);
	Number operator^(const Number& other);

	Number& operator+=(const Number& other);
	Number& operator-=(const Number& other);
	Number& operator*=(const Number& other);
	Number& operator/=(const Number& other);
	Number& operator%=(const Number& other);
	Number& operator^=(const Number& other);

	Number operator-();

	bool operator==(const Number& other);
	bool operator!=(const Number& other);
	bool operator<(const Number& other);
	bool operator>(const Number& other);
	bool operator<=(const Number& other);
	bool operator>=(const Number& other);

	std::vector<uint8_t> get_values() const;
	void set_values(std::vector<uint8_t> values);
	double get_value() const;
	void set_value(double value);
	Bitset2D render() const;
private:
	double _rounded;

	struct NumberNode
	{
		NumberNode* first;
		NumberNode* second;
		double value;
	};

	NumberNode* _root;
};

