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
        /// Appends bs2 to bs1.
        /// </summary>
        static void append(std::vector<dynamic_bitset>& bs1, const std::vector<dynamic_bitset>& bs2);
        /// <summary>
        /// Creates a 2D bitset with the given width and height, all set to value.
        /// </summary>
        static std::vector<dynamic_bitset> create_plane(const int width, const int height, const bool value);
        /// <summary>
        /// Creates a 2D bitset from a 2D vector of uint8_t.
        /// </summary>
        static std::vector<dynamic_bitset> create_plane(const int width, const int height, const std::vector<std::vector<uint8_t>>& plane);
        /// <summary>
        /// Compares two 2D bitsets.
        /// </summary>
        static bool equals(const std::vector<dynamic_bitset>& bs1, const std::vector<dynamic_bitset>& bs2);
        /// <summary>
        /// Converts a 2D bitset to a string.
        /// </summary>
        static std::string to_string(const std::vector<dynamic_bitset>& bs);
        /// <summary>
        /// Converts a 2D bitset to a string with formatting.
        /// </summary>
        static std::string to_string_formatted(const std::vector<dynamic_bitset>& bs);
};