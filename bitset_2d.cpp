#include "bitset_2d.h"

void bitset_2d::append(std::vector<dynamic_bitset> &bs1, const std::vector<dynamic_bitset> &bs2)
{
    bs1.insert(bs1.end(), bs2.begin(), bs2.end());
}

std::vector<dynamic_bitset> bitset_2d::create_plane(const int width, const int height, const bool value)
{
    std::vector<dynamic_bitset> bs = std::vector<dynamic_bitset>(width);
    for (uint32_t i = 0; i < width; i++)
    {
        bs[i] = dynamic_bitset(height, value);
    }
    return bs;
}

std::vector<dynamic_bitset> bitset_2d::create_plane(const int width, const int height, const std::vector<std::vector<uint8_t>> &plane)
{
    std::vector<dynamic_bitset> bs = std::vector<dynamic_bitset>(width);
    for (uint32_t i = 0; i < width; i++)
    {
        bs[i] = dynamic_bitset(plane[i], height);
    }
    return bs;
}

bool bitset_2d::equals(const std::vector<dynamic_bitset> &bs1, const std::vector<dynamic_bitset> &bs2)
{
    if(bs1.size() != bs2.size())
    {
        return false;
    }
    for (uint32_t i = 0; i < bs1.size(); i++)
    {
        if(bs1[i] != bs2[i])
        {
            return false;
        }
    }
    return true;
}

std::string bitset_2d::to_string(const std::vector<dynamic_bitset> &bs)
{
    std::string s = "";
    for (uint32_t i = 0; i < bs.size(); i++)
    {
        s += bs[i].to_string();
    }
    return s;
}

std::string bitset_2d::to_string_formatted(const std::vector<dynamic_bitset>& bs)
{
    uint32_t max_size = 0;
    for (uint32_t i = 0; i < bs.size(); i++)
    {
        if(bs[i].size() > max_size)
        {
            max_size = bs[i].size();
        }
    }

    std::string s = "";
    for(uint32_t i = 0; i < max_size; i++)
    {
        for(uint32_t j = 0; j < bs.size(); j++)
        {
            if(i < bs[j].size())
            {
                s += bs[j][i] ? "1" : "0";
            }
            else
            {
                s += " ";
            }
        }
        s += "\n";
    }
    return s;
}