/*
  ==============================================================================

    SingleDelay.h
    Created: 28 Feb 2022 2:29:22pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SingleDelay {
  int   mMaxSamples, mWriteHead;
  float mMix, mMixInv, mFeedback, mSampleRate, mOutputPrev;
  juce::LinearSmoothedValue<float> mDelaySamples;
  float                        *mBuffer;
  bool  prepared;

public:
  SingleDelay();
  ~SingleDelay();
  void prepare(float delaySeconds, float feedback, float mix, float maxSeconds,
               float sampleRate);
  void setParams(float delaySeconds, float feedback, float mix);
  void processBlock(float *block, int numSamples);
  void processSample(float *const thisSample);
  const bool &isPrepared;
};
