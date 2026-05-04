#pragma once

#include <Arduino.h>

namespace TachometerConfig
{
constexpr uint8_t kSensorPin = 2;

constexpr uint8_t kScreenWidth = 128;
constexpr uint8_t kScreenHeight = 32;
constexpr int8_t kOledResetPin = 4;
constexpr uint8_t kOledAddress = 0x3C;

constexpr unsigned long kNoPulseTimeoutUs = 2000000UL;
constexpr uint8_t kSampleBufferSize = 100;
} // namespace TachometerConfig
