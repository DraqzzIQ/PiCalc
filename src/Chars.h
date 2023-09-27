#pragma once
#include <map>
#include <string>
#include <stdint.h>

class Chars
{
	public:
		static const std::map<std::string, uint8_t> KEY_MAP;
		static const std::map<uint8_t, uint8_t> KEY_MAP_SHIFT;
		static const std::map<uint8_t, uint8_t> KEY_MAP_ALPHA;
};