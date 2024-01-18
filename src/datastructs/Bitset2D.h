#pragma once
#include "datastructs/DynamicBitset.h"
#include <constant/Chars.h>
#include <cstdint>
#include <map>
#include <vector>

/// <summary>
/// Utility for 2D bitsets.
/// </summary>
class Bitset2D
{
	public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Bitset2D();
	/// <summary>
	/// Construct a Bitset2D with given the width and height, all bits set to value
	/// </summary>
	Bitset2D(uint32_t width, uint32_t height, bool value);
	/// <summary>
	/// Construct a Bitset2D with given height, each column is equal to the given DynamicBitset
	/// </summary>
	Bitset2D(uint32_t width, const DynamicBitset& other);
	/// <summary>
	/// Construct a Bitset2D with the given 2d vector of uint8_ts, where each uint8_t represents 8 bits in y-direction
	/// </summary>
	Bitset2D(uint32_t width, uint32_t height, const std::vector<std::vector<uint8_t>>& plane);
	/// <summary>
	/// Copy constructor.
	/// </summary>
	Bitset2D(const Bitset2D& other);
	/// <summary>
	/// Destructor.
	/// </summary>
	~Bitset2D();

	/// <summary>
	/// Returns the DynamicBitset at index.
	/// </summary>
	const DynamicBitset& operator[](uint32_t index) const;
	/// <summary>
	/// Compares two 2D bitsets.
	/// </summary>
	bool operator==(const Bitset2D& other) const;
	/// <summary>
	/// Compares two 2D bitsets.
	/// </summary>
	bool operator!=(const Bitset2D& other) const;
	/// <summary>
	/// Assignment operator.
	/// </summary>
	Bitset2D& operator=(const Bitset2D& other);
	///// <summary>
	///// appends two bitset_2ds together
	///// Very Inefficient due to return by value
	///// </summary>
	// Bitset2D operator+(const Bitset2D& other);

	/// <summary>
	/// Returns the bit at index.
	/// </summary>
	const DynamicBitset& at(uint32_t index) const;
	/// <summary>
	/// Returns the width of the Bitset2D
	/// </summary>
	uint32_t width() const;
	/// <summary>
	/// Returns the height of the Bitset2D
	/// </summary>
	uint32_t height() const;
	/// <summary>
	/// get the value of the bit on the specified coordinates
	/// </summary>
	bool get_bit(uint32_t coord_x, uint32_t coord_y) const;
	/// <summary>
	/// copy part of the Bitset2D from start to end to another Bitset2d
	/// </summary>
	Bitset2D& copy(uint32_t x_start, uint32_t y_start, uint32_t width, uint32_t height, Bitset2D& destination) const;

	/// <summary>
	/// put a string (vector of Keys) on the Bitset2D starting at coord_x, coord_y
	/// </summary>
	void put_chars(uint32_t coord_x, uint32_t coord_y, const std::map<KEY, Bitset2D>& font, KEY_SET text, bool resize_if_needed);
	/// <summary>
	/// Overwrite the Bitset2D with other placed on the position coord_x, coord_y
	/// </summary>
	void set(uint32_t coord_x, uint32_t coord_y, const Bitset2D& other, bool resize_if_needed);
	/// <summary>
	/// Overwrite a column of the Bitset2D with other placed on the x-position coord_x
	/// </summary>
	void set_column(uint32_t coord_x, const DynamicBitset& other);
	/// <summary>
	/// Overwrite the bit on the position coord_x, coord_y with value
	/// </summary>
	void set_bit(uint32_t coord_x, uint32_t coord_y, bool value);
	/// <summary>
	/// inserts a column to the Bitset2D at x_position coord_x
	/// NOT DONE YET
	/// </summary>
	void insert_column(uint32_t coord_x, const DynamicBitset& other);
	/// <summary>
	/// inserts other to the Bitset2D at the specified x-position
	/// NOT DONE YET
	/// </summary>
	void insert_x(uint32_t coord_x, const Bitset2D& other);
	/// <summary>
	/// inserts other to the Bitset2D at the specified y-position
	/// NOT DONE YET
	/// </summary>
	void insert_y(uint32_t coord_y, const Bitset2D& other);
	/// <summary>
	/// Erases the Column at index
	/// </summary>
	void erase_x(uint32_t coord_x);
	/// <summary>
	/// Erases the Row at index
	/// </summary>
	void erase_y(uint32_t coord_y);
	/// <summary>
	/// Erases the Column at index
	/// </summary>
	void pop_back_x();
	/// <summary>
	/// Clears the Bitset2D
	/// </summary>
	void clear();

	/// <summary>
	/// Appends a column to the right of the Bitset2D
	/// </summary>
	void push_back(const DynamicBitset& other);
	/// <summary>
	/// Appends a column to the left of the Bitset2D
	/// </summary>
	void push_front(const DynamicBitset& other);
	/// <summary>
	/// extends the Bitset2D by other in x-direction
	/// </summary>
	void extend_right(const Bitset2D& other);
	/// <summary>
	/// extends the Bitset2D by length in x_direction, all new bits set to value
	/// </summary>
	void extend_right(uint32_t length, bool value);
	/// <summary>
	/// extends the Bitset2D by other in y-direction
	/// </summary>
	void extend_down(const Bitset2D& other);
	/// <summary>
	/// extends the Bitset2D by length in y_direction, all new bits set to value
	/// </summary>
	void extend_down(uint32_t length, bool value);
	/// <summary>
	/// extends the Bitset2D by other in x-direction
	/// </summary>
	void extend_left(const Bitset2D& other);
	/// <summary>
	/// extends the Bitset2D by length in x_direction, all new bits set to value
	/// </summary>
	void extend_left(uint32_t length, bool value);
	/// <summary>
	/// extends the Bitset2D by other in y-direction
	/// </summary>
	void extend_up(const Bitset2D& other);
	/// <summary>
	/// extends the Bitset2D by length in y_direction, all new bits set to value
	/// </summary>
	void extend_up(uint32_t length, bool value);

	/// <summary>
	/// Converts a 2D bitset to a string
	/// </summary>
	std::string to_string() const;
	/// <summary>
	/// Converts a 2D bitset to a string with formatting
	/// </summary>
	std::string to_string_formatted() const;
	/// <summary>
	/// Converts a 2D bitset to a vector of uint8_ts of a bmp file
	/// </summary>
	std::vector<uint8_t> to_bmp();

	/// <summary>
	/// Converts bytes of a bmp file to a 2D bitset
	/// </summary>
	void from_bmp(std::vector<uint8_t> bytes);

	private:
	/// <summary>
	/// The underlying storage type storing the bits.
	/// </summary>
	std::vector<DynamicBitset> _plane;
	/// <summary>
	/// width of the Bitset2D
	/// </summary>
	uint32_t _width;
	/// <summary>
	/// height of the Bitset2D
	/// </summary>
	uint32_t _height;
};
