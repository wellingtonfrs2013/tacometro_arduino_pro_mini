#pragma once

#include <Arduino.h>

#include "display/TachometerDisplay.h"
#include "domain/RpmCalculator.h"

class TachometerApp
{
public:
  bool begin(void (*isrHandler)());
  void loop();
  void onPulseInterrupt();

private:
  TachometerDisplay display;
  RpmCalculator rpmCalculator;
};
