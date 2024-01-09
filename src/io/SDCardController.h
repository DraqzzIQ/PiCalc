#pragma once
#define PICO
#ifdef PICO
#include "io/SDCardHWConfig.h"

class SDCardController
{
	public:
	static bool save_file(std::string dir, std::string filename, const std::vector<uint8_t>& bytes);
	static bool read_file(std::string dir, std::string filename, std::vector<uint8_t>& bytes);
	static void init();

	private:
	static bool ready();
	static void card_detect_callback(uint gpio, uint32_t events);
	static sd_card_t* _sd_card;
};
#endif