/*
  ==============================================================================

    SimpleMCDelay.h
    Created: 28 Feb 2022 2:29:22pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SimpleMCDelay {
  int   mMaxSamples, *mWriteHeads;
  float mMix, mMixInv, mFeedback, mSampleRate, mOutputPrev;
  juce::LinearSmoothedValue<float> mDelaySamples;
  float                           *mBuffers;
  bool                             prepared;

  void processSample(float *const thisSample, float *buffer, int &writeHead);

public:
  SimpleMCDelay();
  ~SimpleMCDelay();
  void prepare(float delaySeconds, float feedback, float mix, float maxSeconds,
               float sampleRate, int numChans);
  void setParams(float delaySeconds, float feedback, float mix);
  void processBlocks(float **blocks, int numChans, int numSamples);
  const bool &isPrepared;
};
