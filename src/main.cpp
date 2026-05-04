#include "app/TachometerApp.h"

namespace
{
TachometerApp app;

void ISR_sensor()
{
  app.onPulseInterrupt();
}
} // namespace

void setup()
{
  if (!app.begin(ISR_sensor))
  {
    for (;;)
    {
    }
  }
}

void loop()
{
  app.loop();
}