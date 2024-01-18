#include "io/ConfigSerializable.h"
#include "ConfigSerializable.h"
#include <string.h>

ConfigSerializable::ConfigSerializable(std::string openai_api_key, std::string wolframalpha_api_key):
	_openai_api_key(openai_api_key),
	_wolframalpha_api_key(wolframalpha_api_key)
{
}


ConfigSerializable::ConfigSerializable()
{
}
std::vector<uint8_t> ConfigSerializable::searialize()
{
	std::vector<uint8_t> bytes = std::vector<uint8_t>(get_total_serialized_size());
	size_t offset = 0;

	memcpy(bytes.data() + offset, _openai_api_key.c_str(), _openai_api_key.size() + 1);
	offset += _openai_api_key.size() + 1;

	memcpy(bytes.data() + offset, _wolframalpha_api_key.c_str(), _wolframalpha_api_key.size() + 1);
	offset += _wolframalpha_api_key.size() + 1;

	return bytes;
}

void ConfigSerializable::desearialize(std::vector<uint8_t> bytes)
{
	size_t offset = 0;

	_openai_api_key = std::string((char*)bytes.data() + offset);
	offset += _openai_api_key.size() + 1;

	_wolframalpha_api_key = std::string((char*)bytes.data() + offset);
	offset += _wolframalpha_api_key.size() + 1;
}

size_t ConfigSerializable::get_total_serialized_size()
{
	// +2 for the null terminators
	return _openai_api_key.size() + _wolframalpha_api_key.size() + 2;
}

std::string ConfigSerializable::get_openai_api_key()
{
	return _openai_api_key;
}
std::string ConfigSerializable::get_wolframalpha_api_key()
{
	return _wolframalpha_api_key;
}
void ConfigSerializable::set_openai_api_key(std::string openai_api_key)
{
	_openai_api_key = openai_api_key;
}
void ConfigSerializable::set_wolframalpha_api_key(std::string wolframalpha_api_key)
{
	_wolframalpha_api_key = wolframalpha_api_key;
}