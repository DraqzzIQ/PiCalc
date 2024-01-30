#pragma once
#include <algorithm>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

using KEY = uint8_t;
using KEY_SET = std::vector<KEY>;

class Chars
{
	public:
	static const std::map<KEY, KEY> KEY_MAP_SHIFT;
	static const std::map<KEY, KEY> KEY_MAP_ALPHA;
	static bool in_key_set(KEY value, const KEY_SET& vector);
};
