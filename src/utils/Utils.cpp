#include "utils/Utils.h"

#ifndef PICO
std::chrono::steady_clock::time_point Utils::_start_point;
#endif

void Utils::sleep_for_ms(int milliseconds)
{
#ifdef PICO
	sleep_ms(milliseconds);
#else
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
}

uint64_t Utils::us_since_boot()
{
#ifdef PICO
	return time_us_64();
#else
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _start_point).count();
#endif
}

#ifndef PICO
void Utils::set_time_start_point()
{
	_start_point = std::chrono::steady_clock::now();
}
#endif

uint32_t Utils::get_total_heap()
{
#ifdef PICO
	extern char __StackLimit, __bss_end__;
	return &__StackLimit - &__bss_end__;
#else
	return 0;
#endif
}

uint32_t Utils::get_free_heap()
{
#ifdef PICO
	struct mallinfo m = mallinfo();
	return get_total_heap() - m.uordblks;
#else
	return 0;
#endif
}

std::vector<std::string> Utils::split_string(std::string string_to_split, char delimiter)
{
	std::vector<std::string> result = std::vector<std::string>(1);

	for (int i = 0; i < string_to_split.size(); i++) {
		if (string_to_split[i] == delimiter || string_to_split[i] == '\n')
			result.push_back("");
		else
			result[result.size() - 1] += string_to_split[i];
	}

	return result;
}

uint32_t Utils::get_string_as_pixel_width(std::string text, FONT& table, uint16_t spacing)
{
	return Graphics::create_text(text, table, spacing).width();
}
