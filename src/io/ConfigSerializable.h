#pragma once
#include "io/ISerializable.h"

class ConfigSerializable: public ISerializable
{
	public:
	ConfigSerializable(std::string openai_api_key, std::string wolframalpha_api_key);
	ConfigSerializable();
	std::string get_openai_api_key()
	{
		return _openai_api_key;
	}
	std::string get_wolframalpha_api_key()
	{
		return _wolframalpha_api_key;
	}
	void set_openai_api_key(std::string openai_api_key)
	{
		_openai_api_key = openai_api_key;
	}
	void set_wolframalpha_api_key(std::string wolframalpha_api_key)
	{
		_wolframalpha_api_key = wolframalpha_api_key;
	}

	protected:
	std::vector<uint8_t> searialize() override;
	void desearialize(std::vector<uint8_t> bytes) override;
	size_t get_total_serialized_size() override;

	private:
	std::string _openai_api_key;
	std::string _wolframalpha_api_key;
};