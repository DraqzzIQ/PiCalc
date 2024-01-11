#pragma once
#include <cstdint>
#include <string>
#include <vector>
#ifdef PICO
#include "io/SDCardController.h"
#else
#include <filesystem>
#endif

#ifdef _WIN32
#pragma warning(disable: 4996)
#endif

/// <summary>
/// Base class for serializable objects.
/// </summary>
class ISerializable
{
	public:
	ISerializable(){};
	/// <summary>
	/// saves the result of searialize() to a file
	/// either on the sd card or in the local filesystem
	/// <param name="dir">
	/// the directory to save the file in
	/// should be the name of the window/application saving the file
	/// </param>
	/// <param name="filename">the name of the file</param>
	/// </summary>
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
	/// <summary>
	/// uses the result of desearialize() to call desearialize()
	/// <param name="dir">
	/// the directory containing the file
	/// </param>
	/// <param name="filename">the name of the file</param>
	/// </summary>
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
	/// <summary>
	/// converts the object to a vector of bytes
	/// </summary>
	virtual std::vector<uint8_t> searialize() = 0;
	/// <summary>
	/// converts a vector of bytes to the object
	/// IMPORTANT: data needs to be recovered in the same order as it was saved
	/// </summary>
	virtual void desearialize(std::vector<uint8_t> bytes) = 0;
	/// <summary>
	/// returns the size of the object in bytes
	/// by adding the size of all members
	/// </summary>
	virtual size_t get_total_serialized_size() = 0;
};