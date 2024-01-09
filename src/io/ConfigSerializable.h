#pragma once
#include "io/ISerializable.h"

class ConfigSerializable: ISerializable
{
	public:
	ConfigSerializable();

	protected:
	std::vector<uint8_t> searialize() override;
	void desearialize(std::vector<uint8_t> bytes) override;
	size_t get_total_serialized_size() override;

	private:
	std::string _openai_api_key;
	std::string _wolframalpha_api_key;
};