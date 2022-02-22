/*
  ==============================================================================

    FMVoice.cpp
    Created: 21 Feb 2022 7:46:49pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "FMVoice.h"

FMVoice::FMVoice() : car(0.f, 2048), mod(0.f, 2048), note(-1), isPlaying(false)
{
}

void FMVoice::play(int note, float ratio, float amt)
{
  m_freq = juce::MidiMessage::getMidiNoteInHertz(note);
  m_ratio.setCurrentAndTargetValue(ratio);
  m_amt.setCurrentAndTargetValue(amt);
  car.resetPhase();
  mod.resetPhase();
  setFreqRatioInternal();
}

void FMVoice::setFreq(float freq)
{
  m_freq = freq;
  setFreqRatioInternal();
}
void FMVoice::setRatio(float ratio)
{
  m_ratio.setTargetValue(ratio);
  setFreqRatioInternal();
}

void FMVoice::setFreqRatioInternal()
{
  car.setFreq(m_freq);
  mod.setFreq(m_freq * m_ratio.getCurrentValue());
}
void  FMVoice::setAmt(float amt) { m_amt.setTargetValue(amt); }

float FMVoice::cycleAndReturn(float rads)
{
  m_ratio.getNextValue();
  float carrierRads = rads * (1. + mod.cycle(rads) * m_amt.getNextValue());
  float amp         = car.cycle(carrierRads);
  return amp;
}