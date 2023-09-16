#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>

/// <summary>
/// A simple dynamic bitset type
/// using std::vector<uint8_t> as the underlying storage type.
/// </summary>
class dynamic_bitset
{
    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        dynamic_bitset();
        /// <summary>
        /// Construct a dynamic_bitset with n bits.
        /// </summary>
        dynamic_bitset(uint32_t count);
        /// <summary>
        /// Construct a dynamic_bitset with n bits, all set to value.
        /// </summary>
        dynamic_bitset(uint32_t count, bool value);
        /// <summary>
        /// Construct a dynamic_bitset out of a vector<uint8_t> using the first n bits.
        /// </summary>
        dynamic_bitset(std::vector<uint8_t> values, uint32_t count);
        /// <summary>
        /// Copy constructor.
        /// </summary>
        dynamic_bitset(const dynamic_bitset& other);
        /// <summary>
        /// Destructor.
        /// </summary>
        ~dynamic_bitset();

        /// <summary>
        /// Construct a dynamic_bitset with n bits, out of the provided bits.
        /// </summary>
        static dynamic_bitset from_bits(uint8_t bits, uint32_t count);

        /// <summary>
        /// Returns the bit at index.
        /// </summary>
        bool operator[](uint32_t index) const;
        /// <summary>
        /// Returns true if equal to other.
        /// </summary>
        bool operator==(const dynamic_bitset& other) const;
        /// <summary>
        /// Returns true if not equal to other.
        /// </summary>
        bool operator!=(const dynamic_bitset& other) const;
        /// <summary>
        /// Assignment operator.
        /// </summary>
        dynamic_bitset& operator=(const dynamic_bitset& other);
        /// <summary>
        /// Sets the bit at index to value.
        /// </summary>
        void set(uint32_t index, bool value);
        /// <summary>
        // TODO: optimize this
        /// Sets bits at index.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void set(uint32_t index, const dynamic_bitset& bits);
        /// <summary>
        /// Returns the bit at index.
        /// </summary>
        bool at(uint32_t index) const;
        /// <summary>
        /// Returns the number of bits in the bitset.
        /// </summary>
        uint32_t size() const;
        /// <summary>
        /// Clears the bitset.
        /// </summary>
        void clear();
        /// <summary>
        /// Appends a bit to the end of the bitset.
        /// </summary>
        void push_back(bool bit);
        /// <summary>
        /// Removes the last bit from the bitset.
        /// </summary>
        void pop_back();
        /// <summary>
        /// Inserts a bit at index.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void insert(uint32_t index, bool bit);
        /// <summary>
        // TODO: optimize this
        /// Inserts bits at index.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void insert(uint32_t index, const dynamic_bitset& bits);
        /// <summary>
        /// Erases the bit at index.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void erase(uint32_t index);
        /// <summary>
        /// Resizes the bitset to n bits.
        /// </summary>
        void resize(uint32_t count);
        /// <summary>
        /// Appends another bitset to the end of this one.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void append(const dynamic_bitset& other);
        /// <summary>
        /// Returns a vector<uint8_t> containing the bits.
        /// </summary>
        std::vector<uint8_t> get_bytes() const;
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