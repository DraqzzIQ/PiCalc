#pragma once
#include "constant/Chars.h"
#include <map>
#include <string>
#include <vector>

using KEY = uint8_t;
using KEY_SET = std::vector<KEY>;

inline KEY_SET key_set_from_string(const std::string& str)
{
	KEY_SET res;
	res.reserve(str.size());
	for (char c : str) res.push_back(c);
}

constexpr uint8_t SCREEN_WIDTH = 96;
constexpr uint8_t SCREEN_HEIGHT = 31;
constexpr uint8_t FPS = 30;
const std::string OS_VERSION = "0.0.1";
