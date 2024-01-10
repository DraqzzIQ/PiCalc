#pragma once
#ifdef PICO
///
#include <f_util.h>
///
#include <hw_config.h>
#include <iostream>
#include <string>
#include <vector>

class SDCardController
{
	public:
	static bool save_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);
	static bool read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes);
	static void init();

	private:
	static bool ready();
	static void card_detect_callback(uint gpio, uint32_t events);
	static bool set_directory(std::string dir);
	static sd_card_t* _sd_card;
};
#endif