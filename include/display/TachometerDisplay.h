#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

class TachometerDisplay
{
public:
  TachometerDisplay();

  bool begin();
  void showStartup();
  void render(long rpmAverage);

private:
  void showWaiting();
  void showRpm(long rpmAverage);

  Adafruit_SSD1306 display;
};
