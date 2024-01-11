#pragma once
#include <cstdint>
#include <string>
#include <vector>
#ifdef PICO
#include "io/SDCardController.h"
#else
#include <filesystem>
#endif

class ISerializable
{
	public:
	ISerializable(){};
	void save_file(std::string dir, std::string filename)
	{
		std::vector<uint8_t> bytes = searialize();
#ifdef PICO
		SDCardController::write_file(dir, filename, &bytes);
#else
		if (!std::filesystem::exists(dir))
			std::filesystem::create_directory(dir);
		FILE* file = fopen((dir + "/" + filename).c_str(), "wb");
		fwrite(bytes.data(), sizeof(uint8_t), bytes.size(), file);
		fclose(file);
#endif
	}
	void load_file(std::string dir, std::string filename)
	{
		std::vector<uint8_t> bytes;
#ifdef PICO
		SDCardController::read_file(dir, filename, &bytes);
#else
		FILE* file = fopen((dir + "/" + filename).c_str(), "rb");
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		bytes.resize(size);
		fseek(file, 0, SEEK_SET);
		fread(bytes.data(), sizeof(uint8_t), size, file);
		fclose(file);
#endif
		desearialize(bytes);
	}

	protected:
	virtual std::vector<uint8_t> searialize() = 0;
	virtual void desearialize(std::vector<uint8_t> bytes) = 0;
	virtual size_t get_total_serialized_size() = 0;
};