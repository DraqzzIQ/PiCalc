#include "Utils.h"

void Utils::sleep_for_ms(int milliseconds)
{
#ifdef PICO
    sleep_ms(milliseconds);
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
}