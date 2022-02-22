#include "WaveTableOsc.h"

WaveTableOsc::WaveTableOsc(float freqInit, int wtSize)
    : mTableLen(2048), mFreq(freqInit), mPhase(0.f), mWavetable(1, mTableLen)
{
  auto *write = mWavetable.getWritePointer(0);
  for (int i = 0; i < mWavetable.getNumSamples(); i++) {
    float currentRad = ((float)i / mWavetable.getNumSamples()) * 2.f * M_PI;
    write[i]         = std::sin(currentRad);
  }
  mRadToTable = (mWavetable.getNumSamples() - 1) / (2.f * M_PI);
}

void  WaveTableOsc::setFreq(float freq) { mFreq.setTargetValue(freq); }
void  WaveTableOsc::oneSamplePassed() { mFreq = mFreq.getNextValue(); }
float WaveTableOsc::lerp(float y0, float y1, float mod)
{
  return (y1 - y0) * mod + y0;
}

float WaveTableOsc::getAmpl()
{
  float x           = mPhase * mRadToTable;
  int   x0          = static_cast<int>(x);
  float mod         = x - x0;
  int   x1          = x0 + 1;
  x1                = x1 >= mTableLen ? x1 % mTableLen : x1;
  const float *tab  = mWavetable.getReadPointer(0);
  float        y0   = tab[x0];
  float        y1   = tab[x1];
  float        ampl = lerp(y0, y1, mod);
  return ampl;
}

void WaveTableOsc::advanceByRads(float rads)
{
  mPhase += rads * mFreq.getNextValue();
  if (mPhase >= 2.f * M_PI) {
    mPhase -= 2.f * M_PI;
  }
}

float WaveTableOsc::cycle(float rads)
{
  float amp = getAmpl();
  advanceByRads(rads);
  return amp;
}
void WaveTableOsc::resetPhase() { mPhase = 0.f; }