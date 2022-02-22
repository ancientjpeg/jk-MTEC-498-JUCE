/*
  ==============================================================================

    FMVoice.h
    Created: 21 Feb 2022 7:46:49pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once
#include "WaveTableOsc.h"
#include <JuceHeader.h>
#include <stack>
#include <unordered_map>

class FMVoice {
  void                             cycle();
  float                            calcAmp();
  void                             setFreqRatioInternal();

  float                            m_freq;
  juce::LinearSmoothedValue<float> m_ratio, m_amt;
  WaveTableOsc                     car, mod;

public:
  FMVoice();
  void  play(int note, float ratio, float amt);
  void  setFreq(float freq);
  void  setRatio(float ratio);
  void  setAmt(float amt);
  float cycleAndReturn(float rads);

  int   note;
  bool  isPlaying;
};

class FMVoiceManager {
  std::stack<FMVoice *>              inactive;
  std::unordered_map<int, FMVoice *> active;
  FMVoice                           *voices_internal;
  float                              m_ratio, m_amt;

public:
  void  startNote(int midiNote, int vel = 127);
  void  stopNote(int midiNote);
  void  setRatio(float ratio);
  void  setAmt(float amt);
  float cycle(float rads);
  FMVoiceManager(int maxVoices);
  ~FMVoiceManager();
};
