#include "app/TachometerApp.h"

#include "config/TachometerConfig.h"

bool TachometerApp::begin(void (*isrHandler)())
{
  if (!display.begin())
  {
    return false;
  }

  pinMode(TachometerConfig::kSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TachometerConfig::kSensorPin), isrHandler, FALLING);

  display.showStartup();
  return true;
}

void TachometerApp::loop()
{
  rpmCalculator.update(micros());
  display.render(rpmCalculator.rpmAverage());
}

void TachometerApp::onPulseInterrupt()
{
  rpmCalculator.onPulseInterrupt(micros());
}
