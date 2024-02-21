#ifndef PICO
#include "io/IOController.h"

const std::string IOController::_root_dir = "persistence";

bool IOController::write_file(std::string dir, std::string filename, const std::vector<uint8_t>* bytes, bool append)
{
	dir = _root_dir + "/" + dir;

	if (!std::filesystem::exists(dir))
		std::filesystem::create_directories(dir);
	FILE* file = fopen((dir + "/" + filename).c_str(), append ? "ab" : "wb");
	if (!file) return false;
	fwrite(bytes->data(), sizeof(uint8_t), bytes->size(), file);
	fclose(file);
	return true;
}

bool IOController::read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes)
{
	dir = _root_dir + "/" + dir;

	FILE* file = fopen((dir + "/" + filename).c_str(), "rb");
	if (!file) return false;
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	bytes->resize(size);
	fseek(file, 0, SEEK_SET);
	fread(bytes->data(), sizeof(uint8_t), size, file);
	fclose(file);
	return true;
}

bool IOController::rename_file(std::string dir, std::string old_filename, std::string new_filename)
{
	dir = _root_dir + "/" + dir;
	if (!std::filesystem::exists(dir + "/" + old_filename)) return false;
	std::filesystem::rename(dir + "/" + old_filename, dir + "/" + new_filename);
	return true;
}

bool IOController::delete_file(std::string dir, std::string filename)
{
	dir = _root_dir + "/" + dir;
	if (!std::filesystem::exists(dir + "/" + filename)) return false;
	std::filesystem::remove(dir + "/" + filename);
	return true;
}

bool IOController::duplicate_file(std::string dir, std::string filename)
{
	dir = _root_dir + "/" + dir;
	if (!std::filesystem::exists(dir + "/" + filename)) return false;
	std::string new_filename = filename;
	new_filename.insert(new_filename.find_last_of('.'), "_copy");
	std::filesystem::copy(dir + "/" + filename, dir + "/" + new_filename);
	return true;
}

bool IOController::file_exists(std::string dir, std::string filename)
{
	return std::filesystem::exists(_root_dir + "/" + dir + "/" + filename);
}

bool IOController::dir_exists(std::string dir)
{
	return std::filesystem::exists(_root_dir + "/" + dir);
}

std::vector<std::string> IOController::list_dir(std::string dir)
{
	dir = _root_dir + "/" + dir;
	std::vector<std::string> files;
	if (!std::filesystem::exists(dir)) return files;

	for (const auto& entry : std::filesystem::directory_iterator(dir))
		files.push_back(entry.path().filename().string());
	return files;
}

#endif