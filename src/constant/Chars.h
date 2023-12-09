#pragma once
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

using KEY = uint16_t;
using KEY_SET = std::vector<KEY>;

class Chars
{
	public:
	static const std::map<std::string, KEY> KEY_MAP;
	static const std::map<KEY, KEY> KEY_MAP_SHIFT;
	static const std::map<KEY, KEY> KEY_MAP_ALPHA;
};
