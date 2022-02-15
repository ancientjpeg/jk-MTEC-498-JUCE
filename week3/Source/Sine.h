#ifndef SINE_H
#define SINE_H

#include <cmath>

class Sine {

  float                    mFreq, mPhase, mDeltaTimeTwoPi;
  float                    lerp(float y0, float y1);
  juce::AudioBuffer<float> mWavetable;
  float                    mRadToTable;

public:
  Sine(int wtSize, float deltaTimeTwoPi);
  void  setDeltaT(float deltaTimeTwoPi);
  void  setFreq(float freq);
  float lerp(float y0, float y1, float mod);
  float getAmpl();
  float newPhase(float by);
}

#endif