/*
  ==============================================================================

    FMVoiceManager.cpp
    Created: 21 Feb 2022 8:28:53pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "FMVoice.h"

typedef std::pair<int, FMVoice *> fmv_t;

FMVoiceManager::FMVoiceManager(int maxVoices)
{
  voices_internal = new FMVoice[maxVoices];
  for (int i = 0; i < maxVoices; i++) {
    inactive.push(voices_internal + i);
  }
}
FMVoiceManager::~FMVoiceManager() { delete voices_internal; }

void FMVoiceManager::startNote(int midiNote, int vel = 127)
{
  if (inactive.empty())
    return;
  FMVoice *newVoice = inactive.top();
  inactive.pop();

  newVoice->play(midiNote);
}

void FMVoiceManager::stopNote(int midiNote)
{
  try {
    inactive.push(active.at(midiNote));
    active.erase(midiNote);
  }
  catch (std::out_of_range) {
    std::cerr << "Note " << midiNote << " is not playing.\n";
  }
  catch (std::exception) {
    std::cerr << "The wrong exception type in stopNote???\n";
  }
}

void FMVoiceManager::setRatio(float ratio)
{
  for (fmv_t v : active) {
    v.second->setRatio(ratio);
  }
}