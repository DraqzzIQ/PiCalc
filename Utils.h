#pragma once
#include <iostream>
#ifdef PICO
#include "pico/stdlib.h"
#include <malloc.h>
#else
#include <thread>
#include <chrono>
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
        static uint64_t us_since_boot();
        static uint32_t get_total_heap();
        static uint32_t get_free_heap();

#ifndef PICO
        static void set_start_point();
        static std::chrono::steady_clock::time_point start_point;
#endif 
	private:
};