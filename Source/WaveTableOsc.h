#ifndef SINE_H
#define SINE_H

#include <JuceHeader.h>

class WaveTableOsc {

  int                              mTableLen;
  float                            mFreq, mPhase, mRadToTable;
  juce::LinearSmoothedValue<float> mFreqSmooth;
  juce::AudioBuffer<float>         mWavetable;

  float                            lerp(float y0, float y1);

public:
  WaveTableOsc(float freqInit, int wtSize);
  void  setFreq(float freq);
  void  oneSamplePassed();
  float getFreq();
  float getPhase();
  float lerp(float y0, float y1, float mod);
  float getAmpl();
  void  advanceByRads(float rads);
};

#endif
