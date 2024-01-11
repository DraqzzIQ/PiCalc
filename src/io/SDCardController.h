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

class SDCardController
{
	public:
	static bool write_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);
	static bool read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);

	private:
	static bool set_directory(std::string dir);
	static bool mount();
	static bool unmount();
};
#endif