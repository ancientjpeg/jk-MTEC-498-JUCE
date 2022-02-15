#ifndef SINE_H
#define SINE_H

#include <JuceHeader.h>

class SineWave {

  int                      mTableLen;
  juce::LinearSmoothedValue<float> mFreqSmooth;
  float                    mFreq, mPhase, mRadToTable;
  juce::AudioBuffer<float> mWavetable;

  float                    lerp(float y0, float y1);

public:
  SineWave(float freqInit, int wtSize);
  void  setFreq(float freq);
  float getFreq();
  float getPhase();
  float lerp(float y0, float y1, float mod);
  float getAmpl();
  void  advanceByRads(float rads);
};

#endif
