#pragma once
#ifdef PICO
///
#include <f_util.h>
///
#include <ff.h> /* Obtains integer types */
///
#include <diskio.h> /* Declarations of disk functions */
//
#include <hw_config.h>
#include <iostream>
#include <string>
#include <vector>

/// <summary>
/// This class is used to read and write files to the sd card.
/// </summary>
class SDCardController
{
	public:
	/// <summary>
	/// writes the given bytes to the given file in the given directory
	/// </summary>
	static bool write_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);
	/// <summary>
	/// reads the given file in the given directory and returns the bytes
	/// </summary>
	static bool read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);
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
};
#endif