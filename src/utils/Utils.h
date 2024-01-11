#pragma once
#include "constant/Graphics.h"
#include <iostream>
#include <vector>
#ifdef PICO
#include "pico/stdlib.h"
#include <malloc.h>
#else
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
	/// <summary>
	/// splits a string on a character
	/// </summary>
	static std::vector<std::string> split_string(std::string string_to_split, char delimiter);
	/// <summary>
	/// gets the width of the visual representation of a string in pixels
	/// for a specific font size
	/// </summary>
	static uint32_t get_string_as_pixel_width(std::string text, FONT& table, uint16_t spacing = 1);
	/// <summary>
	/// sets the start point for the us_since_boot function
	/// </summary>
#ifndef PICO
	static void set_time_start_point();
#endif
	private:
#ifndef PICO
	static std::chrono::steady_clock::time_point _start_point;
#endif
};
