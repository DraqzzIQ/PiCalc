#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

using KEY = uint8_t;
using KEY_SET = std::vector<KEY>;

constexpr uint8_t SCREEN_WIDTH = 96;
constexpr uint8_t SCREEN_HEIGHT = 31;
constexpr uint8_t FPS = 30;
const std::string OS_VERSION = "0.0.1";
