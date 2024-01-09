#pragma once
#include <cstdint>
#include <string>
#include <vector>

class ISerializable
{
	public:
	ISerializable(){};
	void save_file(std::string dir, std::string filename)
	{
		std::vector<uint8_t> bytes = searialize();
#ifdef PICO
#else
		FILE* file = fopen((dir + filename).c_str(), "wb");
		fwrite(bytes.data(), sizeof(uint8_t), bytes.size(), file);
		fclose(file);
#endif
	}
	void load_file(std::string dir, std::string filename)
	{
#ifdef PICO
#else
		FILE* file = fopen((dir + filename).c_str(), "rb");
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);
		std::vector<uint8_t> bytes = std::vector<uint8_t>(size);
		fread(bytes.data(), sizeof(uint8_t), size, file);
		fclose(file);
		desearialize(bytes);
#endif
	}

	protected:
	virtual std::vector<uint8_t> searialize() = 0;
	virtual void desearialize(std::vector<uint8_t> bytes) = 0;
	virtual size_t get_total_serialized_size() = 0;
};