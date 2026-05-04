#include "domain/RpmCalculator.h"

void RpmCalculator::onPulseInterrupt(unsigned long nowMicros)
{
  pulseDurationVolatile = nowMicros - pulseStartedVolatile;
  pulseStartedVolatile = nowMicros;
  timeoutVolatile = false;
  newPulseVolatile = true;
}

void RpmCalculator::update(unsigned long nowMicros)
{
  unsigned long pulseStartedSnapshot = 0;
  unsigned long pulseDurationSnapshot = 0;
  bool timeoutSnapshot = true;
  bool hasNewPulse = false;

  noInterrupts();
  pulseStartedSnapshot = pulseStartedVolatile;
  pulseDurationSnapshot = pulseDurationVolatile;
  timeoutSnapshot = timeoutVolatile;
  hasNewPulse = newPulseVolatile;

  if (newPulseVolatile)
  {
    newPulseVolatile = false;
  }
  interrupts();

  if (((nowMicros - pulseStartedSnapshot) > TachometerConfig::kNoPulseTimeoutUs) &&
      !timeoutSnapshot && !hasNewPulse)
  {
    noInterrupts();
    timeoutVolatile = true;
    interrupts();

    rpmAverageValue = 0;
    n = 0;
    return;
  }

  if (!timeoutSnapshot && hasNewPulse && pulseDurationSnapshot > 0)
  {
    processPulseDuration(pulseDurationSnapshot);
  }
}

long RpmCalculator::rpmAverage() const
{
  return rpmAverageValue;
}

void RpmCalculator::processPulseDuration(unsigned long pulseDurationUs)
{
  const long rpm = 60000000UL / pulseDurationUs;

  rpmReadings[n] = rpm;

  nMax = constrain(
      map(rpmReadings[n], 60, 100000, 0, TachometerConfig::kSampleBufferSize),
      0,
      TachometerConfig::kSampleBufferSize - 1);

  n++;

  if (n > nMax)
  {
    rpmSum = 0;

    for (uint8_t i = 0; i <= nMax; i++)
    {
      rpmSum += rpmReadings[i];
    }

    rpmAverageValue = rpmSum / (nMax + 1);
    n = 0;
  }
}
