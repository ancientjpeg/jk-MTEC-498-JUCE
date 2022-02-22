/*
  ==============================================================================

    FMVoice.h
    Created: 21 Feb 2022 7:46:49pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Sine.h>

class FMVoice {
  void  cycle();
  float calcAmp();

  float phase;

public:
  FMVoice();
  void  startNote();
  void  stopNote();
  float getAmpThisCycle();

  int   note;
  bool  isPlaying;
};
