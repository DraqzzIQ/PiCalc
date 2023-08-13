#pragma once
#ifdef PICO
#include "pico/stdlib.h"
#else
#include <thread>
#endif

/// <summary>
///  provides cross-platform functionality
/// </summary>
class Utils
{
	public:
        /// <summary>
        /// sleeps for the given amount of milliseconds
        /// </summary>
        /// <param name="milliseconds">milliseconds to sleep</param>
		static void sleep_for_ms(int milliseconds);
	private:
};