#include "utils/Utils.h"

#ifndef PICO
std::chrono::steady_clock::time_point Utils::start_point;
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
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_point).count();
#endif
}

#ifndef PICO
void Utils::set_time_start_point()
{
	start_point = std::chrono::steady_clock::now();
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