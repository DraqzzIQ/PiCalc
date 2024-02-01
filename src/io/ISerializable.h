#pragma once
#include <cstdint>
#include <string>
#include <vector>
#ifdef PICO
#include "io/SDCardController.h"
#else

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
	~ISerializable();
	/// <summary>
	/// saves the result of searialize() to a file
	/// either on the sd card or in the local filesystem
	/// <param name="dir">
	/// the directory to save the file in
	/// should be the name of the window/application saving the file
	/// </param>
	/// <param name="filename">the name of the file</param>
	/// </summary>
	void write_file(std::string dir, std::string filename);
	/// <summary>
	/// uses the result to call desearialize()
	/// <param name="dir">
	/// the directory containing the file
	/// </param>
	/// <param name="filename">the name of the file</param>
	/// </summary>
	void read_file(std::string dir, std::string filename);
	/// <summary>
	/// returns true if the file exists
	/// <param name="dir">
	/// the directory containing the file
	/// </param>
	/// <param name="filename">the name of the file</param>
	/// </summary>
	static bool file_exists(std::string dir, std::string filename);
	/// <summary>
	/// returns true if the directory exists
	/// <param name="dir">
	/// the directory to check
	/// </param>
	/// </summary>
	static bool dir_exists(std::string dir);
	/// <summary>
	/// returns all files in the directory
	/// <param name="dir">
	/// the directory to list
	/// </param>
	/// </summary>
	static std::vector<std::string> list_dir(std::string dir);

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