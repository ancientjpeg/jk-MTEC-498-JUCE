#ifndef SINE_H
#define SINE_H

#include <JuceHeader.h>

class WaveTableOsc {

  int                              mTableLen;
  float                            mPhase, mRadToTable;
  juce::LinearSmoothedValue<float> mFreq;
  juce::AudioBuffer<float>         mWavetable;

  float                            lerp(float y0, float y1);

public:
  WaveTableOsc(float freqInit, int wtSize);
  void  setFreq(float freq);
  void  resetPhase();
  void  oneSamplePassed();
  float lerp(float y0, float y1, float mod);
  float getAmpl();
  void  advanceByRads(float rads);
  float cycle(float rads);
};

#endif
