#include "io/ISerializable.h"

ISerializable::~ISerializable()
{
}

void ISerializable::write_file(std::string dir, std::string filename)
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

void ISerializable::read_file(std::string dir, std::string filename)
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

bool ISerializable::file_exists(std::string dir, std::string filename)
{
#ifdef PICO
	return SDCardController::file_exists(dir, filename);
#else
	return std::filesystem::exists(dir + "/" + filename);
#endif
}

bool ISerializable::dir_exists(std::string dir)
{
#ifdef PICO
	return SDCardController::dir_exists(dir);
#else
	return std::filesystem::exists(dir);
#endif
}

std::vector<std::string> ISerializable::list_dir(std::string dir)
{
#ifdef PICO
	return SDCardController::list_dir(dir);
#else
	std::vector<std::string> files;
	for (const auto& entry : std::filesystem::directory_iterator(dir))
		files.push_back(entry.path().filename().string());
	return files;
#endif
}
