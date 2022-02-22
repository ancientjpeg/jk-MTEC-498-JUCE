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
  void         cycle();
  float        calcAmp();

  float        freq, phase, ratio;
  WaveTableOsc car, mod;

public:
  FMVoice();
  void  play(int note);
  void  setRatio(float ratio);
  float getAmpThisCycle();

  int   note;
  bool  isPlaying;
};

class FMVoiceManager {
  std::stack<FMVoice *>              inactive;
  std::unordered_map<int, FMVoice *> active;
  FMVoice                           *voices_internal;

public:
  void startNote(int midiNote, int vel = 127);
  void stopNote(int midiNote);
  void setRatio(float ratio);
  FMVoiceManager(int maxVoices);
  ~FMVoiceManager();
};
