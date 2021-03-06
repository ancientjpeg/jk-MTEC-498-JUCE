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
  float smoothingTime = 2.f;
  mSampleRate = sampleRate;
  mDelaySamples.reset(mSampleRate, smoothingTime);
  mFeedBack.reset(mSampleRate, smoothingTime);
  setParams(delaySeconds, feedback, mix);
  mDelaySamples.setCurrentAndTargetValue(delaySeconds * mSampleRate);
  mFeedBack.setCurrentAndTargetValue(feedback);
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
  mFeedBack.setTargetValue(feedback);
}

void SimpleMCDelay::processBlocks(float **blocks, int numChans, int numSamples)
{
  for (int i = 0; i < numSamples; i++) {
    for (int chan = 0; chan < numChans; chan++) {
      if (chan == 0){
        m_samp_feedback = mFeedBack.getNextValue();
        m_samp_del_samps = mDelaySamples.getNextValue();
      }
      float *thisBuf = mBuffers + chan * mMaxSamples;
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
  
  // OKAY I COULD BE WRONG
}

void SimpleMCDelay::processSample(float *const thisSample, float *buffer,
                                  int &writeHead)
{
  float rawWrite      = *thisSample + m_samp_feedback * mOutputPrev;
  buffer[writeHead++] = std::tanh(rawWrite);
  writeHead           = writeHead >= mMaxSamples ? 0 : writeHead;

  float readPos       = (float)writeHead - m_samp_del_samps;
  if (readPos < 0.f)
    readPos += (float)mMaxSamples;

  int x0      = (int)readPos;
  int x1      = x0 + 1;
  x1          = x1 < mMaxSamples ? x1 : x1 - mMaxSamples ;
  float mod   = readPos - (float)x0;

  float y0    = buffer[x0];
  float y1    = buffer[x1];

  float outputLerp = (y1 - y0) * mod + y0;
  mOutputPrev = *thisSample * mMixInv + outputLerp * mMix;
  *thisSample = mOutputPrev;
}
