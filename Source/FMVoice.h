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

class FMVoiceManager : public juce::MidiKeyboardStateListener {
  std::stack<FMVoice *>              inactive;
  std::unordered_map<int, FMVoice *> active;
  FMVoice                           *voices_internal;
  float                              m_ratio, m_amt;

public:
  FMVoiceManager(int maxVoices, float ratio_init, float amt_init);
  ~FMVoiceManager();
  void  startNote(int midiNote, float vel);
  void  stopNote(int midiNote);
  void  setRatio(float ratio);
  void  setAmt(float amt);
  float cycle(float rads);
  void  handleNoteOn(juce::MidiKeyboardState *source, int midiChannel,
                     int midiNoteNumber, float velocity) override;
  void  handleNoteOff(juce::MidiKeyboardState *source, int midiChannel,
                      int midiNoteNumber, float velocity) override;

};
