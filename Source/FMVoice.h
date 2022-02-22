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
#include <vector>

class FMVoice {
  void         cycle();
  float        calcAmp();

  float        freq, phase, ratio;
  WaveTableOsc car, mod;

public:
  FMVoice();
  void  startNote();
  void  stopNote();
  float getAmpThisCycle();

  int   note;
  bool  isPlaying;
};

class FMVoiceManager {
  std::stack<FMVoice *>  inactive;
  std::vector<FMVoice *> active;
  FMVoice               *voices_internal;

public:
  FMVoiceManager(int maxVoices);
  ~FMVoiceManager();
};
