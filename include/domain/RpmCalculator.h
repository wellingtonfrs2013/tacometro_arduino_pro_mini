#pragma once

#include <Arduino.h>

#include "config/TachometerConfig.h"

class RpmCalculator
{
public:
  void onPulseInterrupt(unsigned long nowMicros);
  void update(unsigned long nowMicros);

  long rpmAverage() const;

private:
  void processPulseDuration(unsigned long pulseDurationUs);

  volatile unsigned long pulseStartedVolatile = 0;
  volatile unsigned long pulseDurationVolatile = 0;
  volatile bool timeoutVolatile = true;
  volatile bool newPulseVolatile = false;

  long rpmSum = 0;
  long rpmReadings[TachometerConfig::kSampleBufferSize] = {0};
  long rpmAverageValue = 0;
  uint8_t nMax = 0;
  uint8_t n = 0;
};
