/*
  ==============================================================================

    SimpleMCDelay.cpp
    Created: 28 Feb 2022 2:29:22pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "SimpleMCDelay.h"

SimpleMCDelay::SimpleMCDelay()
    : mOutputPrev(0.f), prepared(false), isPrepared(prepared)
{
}
SimpleMCDelay::~SimpleMCDelay()
{
  if (prepared) {
    delete[] mWriteHeads;
    delete[] mBuffers;
  }
}

void SimpleMCDelay::prepare(float delaySeconds, float feedback, float mix,
                            float maxSeconds, float sampleRate, int numChans)
{
  mSampleRate = sampleRate;
  mDelaySamples.setCurrentAndTargetValue(delaySeconds * mSampleRate);
  mFeedback.setCurrentAndTargetValue(feedback);
  setParams(delaySeconds, feedback, mix);
  mMaxSamples = std::ceil(maxSeconds * mSampleRate);
  mBuffers    = new float[mMaxSamples * numChans];
  mWriteHeads = new int[numChans];
  prepared    = true;
}

void SimpleMCDelay::setParams(float delaySeconds, float feedback, float mix)
{
  mMix    = mix;
  mMixInv = 1.f - mMix;
  mDelaySamples.setTargetValue(delaySeconds * mSampleRate);
  mFeedback.setTargetValue(feedback);
}

void SimpleMCDelay::processBlocks(float **blocks, int numChans, int numSamples)
{
  for (int chan = 0; chan < numChans; chan++) {
    float *thisBuf = mBuffers + chan * mMaxSamples;
    for (int i = 0; i < numSamples; i++) {
      processSample(blocks[chan] + i, thisBuf, mWriteHeads[chan]);
    }
  }
}

float sigmoid_n1_1(float input)
{
  // sigmoid * 2.f - 1.f results in:
  // 2/(1-e^-x) - (1-e^-x)/(1-e^-x) == 1+e^-x/1-e^-x
  float expnt = std::exp(-input);
  return (1.f + expnt) / (1.f - expnt);
}

void SimpleMCDelay::processSample(float *const thisSample, float *buffer,
                                  int &writeHead)
{
  float rawWrite      = *thisSample + mFeedback * mOutputPrev;
  buffer[writeHead++] = sigmoid_n1_1(rawWrite);
  writeHead           = writeHead >= mMaxSamples ? 0 : writeHead;

  float readPos       = (float)writeHead - mDelaySamples.getNextValue();
  if (readPos < 0.f)
    readPos += (float)mMaxSamples;

  int x0      = (int)readPos;
  int x1      = x0 + 1;
  x1          = x1 > mMaxSamples ? x1 - mMaxSamples : x1;
  float mod   = readPos - (float)x0;

  float y0    = buffer[x0];
  float y1    = buffer[x1];

  mOutputPrev = (y1 - y0) * mod + y0;
  *thisSample = mOutputPrev;
}
