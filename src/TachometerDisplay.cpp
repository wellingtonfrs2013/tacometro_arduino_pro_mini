#include "display/TachometerDisplay.h"

#include "config/TachometerConfig.h"

TachometerDisplay::TachometerDisplay()
    : display(
          TachometerConfig::kScreenWidth,
          TachometerConfig::kScreenHeight,
          &Wire,
          TachometerConfig::kOledResetPin)
{
}

bool TachometerDisplay::begin()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, TachometerConfig::kOledAddress))
  {
    return false;
  }

  display.setRotation(2);
  return true;
}

void TachometerDisplay::showStartup()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(18, 2);
  display.print(F("STEMAKER"));
  display.display();
  delay(1500);
}

void TachometerDisplay::render(long rpmAverage)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (rpmAverage == 0)
  {
    showWaiting();
    return;
  }

  showRpm(rpmAverage);
}

void TachometerDisplay::showWaiting()
{
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print(F("Aguardando"));
  display.setCursor(28, 10);
  display.print(F("leitura..."));
  display.display();
}

void TachometerDisplay::showRpm(long rpmAverage)
{
  if (rpmAverage < 100000)
  {
    display.setTextSize(3);
    display.setCursor(18, 0);
    display.print(rpmAverage);

    display.setTextSize(1);
    display.setCursor(104, 3);
    display.print(F("RPM"));

    display.display();
    return;
  }

  display.setTextSize(2);
  display.setCursor(13, 8);
  display.print(F("MAX LIMIT"));
  display.display();
}
