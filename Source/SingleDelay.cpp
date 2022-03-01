/*
  ==============================================================================

    SingleDelay.cpp
    Created: 28 Feb 2022 2:29:22pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "SingleDelay.h"

SingleDelay::SingleDelay()
    : mWriteHead(0), mOutputPrev(0.f), prepared(false), isPrepared(prepared)
{
}
SingleDelay::~SingleDelay()
{
  if (prepared)
    delete[] mBuffer;
}

void SingleDelay::prepare(float delaySeconds, float feedback, float mix,
                          float maxSeconds, float sampleRate)
{
  mSampleRate = sampleRate;
  mDelaySamples.setCurrentAndTargetValue(delaySeconds * mSampleRate);
  setParams(delaySeconds, feedback, mix);
  mMaxSamples = std::ceil(maxSeconds * mSampleRate);
  mBuffer     = new float[mMaxSamples];
  prepared    = true;
}

void SingleDelay::setParams(float delaySeconds, float feedback, float mix)
{
  mDelaySamples.setTargetValue(delaySeconds * mSampleRate);
  mMix      = mix;
  mMixInv   = 1.f - mMix;
  mFeedback = feedback;
}

void SingleDelay::processBlock(float *block, int numSamples)
{
  for (int i = 0; i < numSamples; i++) {
    processSample(block + i);
  }
}

void SingleDelay::processSample(float *const thisSample)
{
  mBuffer[mWriteHead++] = *thisSample + mFeedback * mOutputPrev;
  mWriteHead            = mWriteHead >= mMaxSamples ? 0 : mWriteHead;

  float mod             = (float)mWriteHead - mDelaySamples.getNextValue();
  if (mod < 0.f)
    mod += (float)mMaxSamples;
  int x0 = std::floor(mod);
  int x1 = x0 + 1;
  x1     = x1 > mMaxSamples ? x1 - mMaxSamples : x1;
  mod -= (float)x0;

  float y0    = mBuffer[x0];
  float y1    = mBuffer[x1];

  mOutputPrev = (y1 - y0) * mod + y0;
  *thisSample = mOutputPrev;
}
