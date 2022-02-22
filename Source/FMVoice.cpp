/*
  ==============================================================================

    FMVoice.cpp
    Created: 21 Feb 2022 7:46:49pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "FMVoice.h"

FMVoice::FMVoice()
    : freq(0.f), phase(0.f), ratio(1.f), car(freq, 2048), mod(freq, 2048),
      note(-1), isPlaying(false)
{
}

void FMVoice::play(int note)
{
  float freq = juce::MidiMessage::getMidiNoteInHertz(note);
}