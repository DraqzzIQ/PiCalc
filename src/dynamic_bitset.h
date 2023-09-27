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
        /// Construct a dynamic_bitset with n bits, all bits set to value.
        /// </summary>
        dynamic_bitset(uint32_t count, bool value);
        /// <summary>
        /// Construct a dynamic_bitset out of a vector<uint8_t> using the first n bits.
        /// </summary>
        dynamic_bitset(uint32_t count, std::vector<uint8_t> values);
        /// <summary>
        /// Construct a dynamic_bitset out of a vector<bool> using the first n bits.
        /// </summary>
        dynamic_bitset(uint32_t count, const std::vector<bool> values);
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
        /// If not Working: manual comparison
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
        /// Appends two dynamic_bitsets together
        /// </summary>
        dynamic_bitset operator+(const dynamic_bitset& other);

        /// <summary>
        /// Returns the bit at index.
        /// </summary>
        bool at(uint32_t index) const;
        /// <summary>
        /// Returns the number of bits in the bitset.
        /// </summary>
        uint32_t size() const;
        /// <summary>
        /// Returns a vector<uint8_t> containing the bits.
        /// </summary>
        std::vector<uint8_t> get_bytes() const;

        /// <summary>
        /// Sets the bit at index to value.
        /// If not Working: manual comparison
        /// </summary>
        void set(uint32_t index, bool value);
        /// <summary>
        // TODO: optimize this
        /// Sets bits at index.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void set(uint32_t index, const dynamic_bitset& bits);
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
        /// Resizes the bitset to n bits.
        /// </summary>
        void resize(uint32_t count);
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
        /// Removes the last bit from the bitset.
        /// </summary>
        void pop_back();
        /// <summary>
        /// Appends another bitset to the end of this one.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void extend(const dynamic_bitset& other);
        /// <summary>
        /// Appends length bits to the dynamic_bitset, all set to value
        /// TODO: optimize
        /// </summary>
        void extend(uint32_t length, bool value);
        /// <summary>
        /// Appends another bitset to the start of this one.
        /// should be used carefully, as it is O(n).
        /// </summary>
        void extend_left(const dynamic_bitset& other);
        /// <summary>
        /// Appends length bits to the start of the dynamic_bitset, all set to value
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