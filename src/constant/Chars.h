#pragma once
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

class Chars
{
	public:
	static const std::vector<std::string> KEY_MAP;
	static const std::map<std::string, uint8_t> CHAR_TO_KEYCODE;
	static const std::map<uint8_t, uint8_t> KEY_MAP_SHIFT;
	static const std::map<uint8_t, uint8_t> KEY_MAP_ALPHA;
};
