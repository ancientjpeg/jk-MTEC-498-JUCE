/*
  ==============================================================================

    FMVoiceManager.cpp
    Created: 21 Feb 2022 8:28:53pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "FMVoice.h"

FMVoiceManager::FMVoiceManager(int maxVoices) : m_ratio(1.f)
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

  newVoice->play(midiNote, m_ratio, m_amt);
  active[midiNote] = newVoice;
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
  for (auto &[key, v] : active) {
    v->setRatio(ratio);
  }
}

void FMVoiceManager::setAmt(float amt)
{
  for (auto &[key, v] : active) {
    v->setAmt(amt);
  }
}

float FMVoiceManager::cycle(float rads)
{
  float ret = 0.f;
  for (auto &[key, v] : active) {
    ret += v->cycleAndReturn(rads);
  }
  return ret;
}