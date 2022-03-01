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
  setParams(delaySeconds, feedback, mix);
  mMaxSamples = std::ceil(maxSeconds * mSampleRate);
  mBuffers    = new float[mMaxSamples * numChans];
  mWriteHeads = new int[numChans];
  prepared    = true;
}

void SimpleMCDelay::setParams(float delaySeconds, float feedback, float mix)
{
  mDelaySamples.setTargetValue(delaySeconds * mSampleRate);
  mMix      = mix;
  mMixInv   = 1.f - mMix;
  mFeedback = feedback;
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

void SimpleMCDelay::processSample(float *const thisSample, float *buffer,
                                  int &writeHead)
{
  buffer[writeHead++] = *thisSample + mFeedback * mOutputPrev;
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
