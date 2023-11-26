#pragma once
#include <iostream>
#ifdef PICO
#include "http/PicoHttpClient.h"
#include "pico/stdlib.h"
#include <malloc.h>
#else
#include "http/DesktopHttpClient.h"
#include <chrono>
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
	/// <summary>
	/// returns the number of microseconds since boot
	/// </summary>
	static uint64_t us_since_boot();
	/// <summary>
	/// returns the total heap size in bytes
	/// </summary>
	static uint32_t get_total_heap();
	/// <summary>
	/// returns the free heap size in bytes
	/// </summary>
	static uint32_t get_free_heap();

#ifndef PICO
	/// <summary>
	/// sets the start point for the us_since_boot function
	/// </summary>
	static void set_time_start_point();
	static std::chrono::steady_clock::time_point start_point;
#endif
	private:
};
