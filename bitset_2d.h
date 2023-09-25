#pragma once
#include <vector>
#include <cstdint>
#include "dynamic_bitset.h"

/// <summary>
/// Utility for 2D bitsets.
/// </summary>
class bitset_2d
{
    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        bitset_2d();
        /// <summary>
        /// Construct a bitset_2d with given the width and height, all bits set to value
        /// </summary>
        bitset_2d(uint32_t width, uint32_t height, bool value);
        /// <summary>
        /// Construct a bitset_2d with given height, each row is equal to the given dynamic_bitset
        /// </summary>
        bitset_2d(uint32_t width, const dynamic_bitset &other);
        /// <summary>
        /// Construct a bitset_2d with the given 2d vector of uint8_ts, where each uint8_t represents 8 bits in y-direction
        /// </summary>
        bitset_2d(uint32_t width, uint32_t height, const std::vector<std::vector<uint8_t>> &plane);
        /// <summary>
        /// Copy constructor.
        /// </summary>
        bitset_2d(const bitset_2d &other);
        /// <summary>
        /// Destructor.
        /// </summary>
        ~bitset_2d();

        /// <summary>
        /// Returns the dynamic_bitset at index.
        /// </summary>
        const dynamic_bitset& operator[](uint32_t index) const;
        /// <summary>
        /// Compares two 2D bitsets.
        /// </summary>
        bool operator==(const bitset_2d& other) const;
        /// <summary>
        /// Compares two 2D bitsets.
        /// </summary>
        bool operator!=(const bitset_2d& other) const;
        /// <summary>
        /// Assignment operator.
        /// </summary>
        bitset_2d& operator=(const bitset_2d& other);
        /// <summary>
        /// appends two bitset_2ds together
        /// Very Inefficient due to return by value
        /// </summary>
        bitset_2d operator+(const bitset_2d& other);

        /// <summary>
        /// Returns the bit at index.
        /// </summary>
        const dynamic_bitset& at(uint32_t index) const;
        /// <summary>
        /// Returns the width of the bitset_2d
        /// </summary>
        uint32_t width() const;
        /// <summary>
        /// Returns the height of the bitset_2d
        /// </summary>
        uint32_t height() const;
        /// <summary>
        /// get the value of the bit on the specified coordinates
        /// </summary>
        bool get_bit(uint32_t coord_x, uint32_t coord_y) const;

        /// <summary>
        /// Overwrite the bitset_2d with other placed on the position coord_x, coord_y
        /// </summary>
        void set(uint32_t coord_x, uint32_t coord_y, const bitset_2d& other, bool resize_if_needed);
        /// <summary>
        /// Overwrite a column of the bitset_2d with other placed on the x-position coord_x
        /// </summary>
        void set_column(uint32_t coord_x, const dynamic_bitset& other);
        /// <summary>
        /// Overwrite the bit on the position coord_x, coord_y with value
        /// </summary>
        void set_bit(uint32_t coord_x, uint32_t coord_y, bool value);
        /// <summary>
        /// inserts a column to the bitset_2d at x_position coord_x
        /// NOT DONE YET
        /// </summary>
        void insert_column(uint32_t coord_x, const dynamic_bitset& other);
        /// <summary>
        /// inserts other to the bitset_2d at the specified x-position
        /// NOT DONE YET
        /// </summary>
        void insert_x(uint32_t coord_x, const bitset_2d& other);
        /// <summary>
        /// inserts other to the bitset_2d at the specified y-position
        /// NOT DONE YET
        /// </summary>
        void insert_y(uint32_t coord_y, const bitset_2d& other);
        /// <summary>
        /// Erases the Column at index
        /// </summary>
        void erase_x(uint32_t coord_x);
        /// <summary>
        /// Erases the Row at index
        /// </summary>
        void erase_y(uint32_t coord_y);
        /// <summary>
        /// Clears the bitset_2d
        /// </summary>
        void clear();

        /// <summary>
        /// Appends a column to the right of the bitset_2d
        /// </summary>
        void push_back(const dynamic_bitset& other);
        /// <summary>
        /// Appends a column to the left of the bitset_2d
        /// </summary>
        void push_front(const dynamic_bitset& other);
        /// <summary>
        /// extends the bitset_2d by other in x-direction
        /// </summary>
        void extend_right(const bitset_2d &other);
        /// <summary>
        /// extends the bitset_2d by length in x_direction, all new bits set to value
        /// </summary>
        void extend_right(uint32_t length, bool value);
        /// <summary>
        /// extends the bitset_2d by other in y-direction
        /// </summary>
        void extend_down(const bitset_2d& other);
        /// <summary>
        /// extends the bitset_2d by length in y_direction, all new bits set to value
        /// </summary>
        void extend_down(uint32_t length, bool value);
        /// <summary>
        /// extends the bitset_2d by other in x-direction
        /// </summary>
        void extend_left(const bitset_2d& other);
        /// <summary>
        /// extends the bitset_2d by length in x_direction, all new bits set to value
        /// </summary>
        void extend_left(uint32_t length, bool value);
        /// <summary>
        /// extends the bitset_2d by other in y-direction
        /// </summary>
        void extend_up(const bitset_2d& other);
        /// <summary>
        /// extends the bitset_2d by length in y_direction, all new bits set to value
        /// </summary>
        void extend_up(uint32_t length, bool value);

        /// <summary>
        /// Converts a 2D bitset to a string
        /// </summary>
        std::string to_string();
        /// <summary>
        /// Converts a 2D bitset to a string with formatting
        /// </summary>
        std::string to_string_formatted();
    private:
        /// <summary>
        /// The underlying storage type storing the bits.
        /// </summary>
        std::vector<dynamic_bitset> _plane;
        /// <summary>
        /// width of the bitset_2d
        /// </summary>
        uint32_t _width;
        /// <summary>
        /// height of the bitset_2d
        /// </summary>
        uint32_t _height;
};