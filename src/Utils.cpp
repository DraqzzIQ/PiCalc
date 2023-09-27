#include "Utils.h"

void Utils::sleep_for_ms(int milliseconds)
{
#ifdef PICO
    sleep_ms(milliseconds);
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
}

uint32_t Utils::get_total_heap() {
#ifdef PICO
   extern char __StackLimit, __bss_end__;
   return &__StackLimit  - &__bss_end__;
#else
    return 0;
#endif
}

uint32_t Utils::get_free_heap() {
#ifdef PICO
   struct mallinfo m = mallinfo();
   return get_total_heap() - m.uordblks;
#else
   return 0;
#endif
}