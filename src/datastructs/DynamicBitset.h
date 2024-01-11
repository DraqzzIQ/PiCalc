#pragma once
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

/// <summary>
/// A simple dynamic bitset type
/// using std::vector of uint8_t as the underlying storage type.
/// </summary>
class DynamicBitset
{
	public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	DynamicBitset();
	/// <summary>
	/// Construct a DynamicBitset with n bits, all bits set to value.
	/// </summary>
	DynamicBitset(uint32_t count, bool value);
	/// <summary>
	/// Construct a DynamicBitset out of a vector of uint8_t using the first n bits.
	/// </summary>
	DynamicBitset(uint32_t count, std::vector<uint8_t> values);
	/// <summary>
	/// Construct a DynamicBitset out of a vector of bool using the first n bits.
	/// </summary>
	DynamicBitset(uint32_t count, const std::vector<bool> values);
	/// <summary>
	/// Copy constructor.
	/// </summary>
	DynamicBitset(const DynamicBitset& other);
	/// <summary>
	/// Destructor.
	/// </summary>
	~DynamicBitset();

	/// <summary>
	/// Construct a DynamicBitset with n bits, out of the provided bits.
	/// </summary>
	static DynamicBitset from_bits(uint8_t bits, uint32_t count);

	/// <summary>
	/// Returns the bit at index.
	/// </summary>
	bool operator[](uint32_t index) const;
	/// <summary>
	/// Returns true if equal to other.
	/// If not Working: manual comparison
	/// </summary>
	bool operator==(const DynamicBitset& other) const;
	/// <summary>
	/// Returns true if not equal to other.
	/// </summary>
	bool operator!=(const DynamicBitset& other) const;
	/// <summary>
	/// Assignment operator.
	/// </summary>
	DynamicBitset& operator=(const DynamicBitset& other);
	/// <summary>
	/// Appends two dynamic_bitsets together
	/// </summary>
	DynamicBitset operator+(const DynamicBitset& other);

	/// <summary>
	/// Returns the bit at index.
	/// </summary>
	bool at(uint32_t index) const;
	/// <summary>
	/// Returns the number of bits in the bitset.
	/// </summary>
	uint32_t size() const;
	/// <summary>
	/// Returns a vector of uint8_t containing the bits.
	/// </summary>
	std::vector<uint8_t> get_bytes() const;
	/// <summary>
	/// copy width bits starting at start to another DynamicBitset
	/// </summary>
	/// <param name="start"></param>
	/// <param name="width"></param>
	/// <returns></returns>
	DynamicBitset copy(uint32_t start, uint32_t width) const;

	/// <summary>
	/// Sets the bit at index to value.
	/// If not Working: manual comparison
	/// </summary>
	void set(uint32_t index, bool value);
	/// <summary>
	/// Sets bits at index.
	/// </summary>
	void set(uint32_t index, const DynamicBitset& bits);
	/// <summary>
	/// Inserts a bit at index.
	/// VERY INEFFICIENT
	/// </summary>
	void insert(uint32_t index, bool bit);
	/// <summary>
	/// Inserts bits at index.
	/// VERY INEFFICIENT
	/// </summary>
	void insert(uint32_t index, const DynamicBitset& bits);
	/// <summary>
	/// Erases the bit at index.
	/// should be used carefully, as it is O(n).
	/// </summary>
	void erase(uint32_t index);
	/// <summary>
	/// Clears the bitset.
	/// </summary>
	void clear();

	/// <summary>
	/// Appends a bit to the end of the bitset.
	/// </summary>
	void push_back(bool bit);
	/// <summary>
	/// Appends a bit to the start of the bitset.
	/// </summary>
	void push_front(bool bit);
	/// <summary>
	/// Removes the last bit from the bitset.
	/// </summary>
	void pop_back();
	/// <summary>
	/// Removes the first bit from the bitset.
	/// </summary>
	void pop_front();
	/// <summary>
	/// Appends another bitset to the end of this one.
	/// should be used carefully, as it is O(n).
	/// </summary>
	void extend(const DynamicBitset& other);
	/// <summary>
	/// Appends length bits to the DynamicBitset, all set to value
	/// VERY INEFFICIENT
	/// </summary>
	void extend(uint32_t length, bool value);
	/// <summary>
	/// Appends another bitset to the start of this one.
	/// should be used carefully, as it is O(n).
	/// </summary>
	void extend_left(const DynamicBitset& other);
	/// <summary>
	/// Appends length bits to the start of the DynamicBitset, all set to value
	/// VERY INEFFICIENT
	/// </summary>
	void extend_left(uint32_t length, bool value);

	/// <summary>
	/// Returns a string representation of the bitset.
	/// </summary>
	std::string to_string() const;
	/// <summary>
	/// Returns a formatted string representation of the bitset.
	/// </summary>
	std::string to_string_formatted(uint32_t bytes_per_line = 4) const;

	private:
	/// <summary>
	/// The underlying storage type storing the bits.
	/// </summary>
	std::vector<uint8_t> _bits;
	/// <summary>
	/// The number of bits in the bitset.
	/// </summary>
	uint32_t _bit_count;
};
