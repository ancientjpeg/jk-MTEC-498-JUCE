#include "Sine.h"

Sine::Sine(int wtSize, float deltaTimeTwoPi)
    : mFreq(0.f), mPhase(0.f), mDeltaTimeTwoPi(deltaTimeTwoPi),
      mWavetable(1, 2048)
{
  mRadToTable = (mWavetable.getNumSamples() - 1) / (2.f * M_PI);
}

void Sine::setDeltaT(float deltaTimeTwoPi) { mDeltaTimeTwoPi = deltaTimeTwoPi; }
void Sine::setFreq(float freq) { mFreq = freq; }
float Sine::lerp(float y0, float y1, float mod) { return (y1 - y0) * mod + y0; }
float Sine::getAmpl() { mPhase * }

float Sine::newPhase(float by)
{
  mPhase += mFreq * mDeltaTimeTwoPi;
  if (mPhase >= 2.f * M_PI) {
    mPhase -= 2.f * M_PI;
  }
}
