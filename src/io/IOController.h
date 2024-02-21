#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#ifdef PICO
#include <f_util.h>
//
#include <ff.h> // Obtains integer types
//
#include <diskio.h> // Declarations of disk functions
//
#include <hw_config.h>
#else
#include <filesystem>
#endif

#ifdef _WIN32
#pragma warning(disable: 4996) // disable warning about fopen
#endif

/// <summary>
/// This class is used to read and write files to sd card or filesystem
/// </summary>
class IOController
{
	public:
	/// <summary>
	/// writes the given bytes to the given file in the given directory
	/// </summary>
	static bool write_file(std::string dir, std::string filename, const std::vector<uint8_t>* bytes, bool append = false);
	/// <summary>
	/// reads the given file in the given directory and returns the bytes
	/// </summary>
	static bool read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);
	/// <summary>
	/// renames the given file in the given directory
	/// </summary>
	static bool rename_file(std::string dir, std::string old_filename, std::string new_filename);
	/// <summary>
	/// deletes the given file in the given directory
	/// </summary>
	static bool delete_file(std::string dir, std::string filename);
	/// <summary>
	/// dublicates the given file in the given directory, adding a number to the end of the filename
	/// </summary>
	static bool duplicate_file(std::string dir, std::string filename);
	/// <summary>
	/// returns true if the file exists
	/// </summary>
	static bool file_exists(std::string dir, std::string filename);
	/// <summary>
	/// returns true if the directory exists
	/// </summary>
	static bool dir_exists(std::string dir);
	/// <summary>
	/// returns all files in the directory
	/// </summary>
	static std::vector<std::string> list_dir(std::string dir);

	private:
#ifdef PICO
	/// <summary>
	/// sets the current directory to the given directory
	/// </summary>
	static bool set_directory(std::string dir);
	/// <summary>
	/// mounts the sd card
	/// </summary>
	static bool mount();
	/// <summary>
	/// unmounts the sd card
	/// </summary>
	static bool unmount();
#else
	/// <summary>
	/// folder where the files are stored on PC
	/// </summary>
	static const std::string _root_dir;
#endif
};