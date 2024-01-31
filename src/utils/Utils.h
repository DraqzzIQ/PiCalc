#pragma once
#include "constant/Constants.h"
#include "constant/Graphics.h"
#include <iostream>
#include <vector>
#ifdef PICO
#include "hardware/adc.h"
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
	static void sleep_for_ms(uint64_t milliseconds);
	/// <summary>
	/// sleeps for the given amount of microseconds
	/// </summary>
	/// <param name="milliseconds">microseconds to sleep</param>
	static void sleep_for_us(uint64_t microseconds);
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
	/// returns true if the KEY is in the KEY_SET
	/// </summary>
	static bool in_key_set(KEY value, const KEY_SET& vector);
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
	/// update the Battery Voltage stored in voltage and whether the battery is charged (stored in charging)
	/// </summary>
	static void update_voltage();
	/// <summary>
	/// the current Battery Voltage, with 5 decimal places
	/// </summary>
	static uint32_t voltage;
	/// <summary>
	/// stores whether the battery is currently charging
	/// </summary>
	static bool charging;
#ifndef PICO
	/// <summary>
	/// sets the start point for the us_since_boot function
	/// </summary>
	static void set_time_start_point();
#endif
	private:
#ifndef PICO
	static std::chrono::steady_clock::time_point _start_point;
#endif
};
