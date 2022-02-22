/*
  ==============================================================================

    FMVoiceManager.cpp
    Created: 21 Feb 2022 8:28:53pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "FMVoice.h"

FMVoiceManager::FMVoiceManager(int maxVoices)
{
  voices_internal = new FMVoice[maxVoices];
  for (int i = 0; i < maxVoices; i++) {
    inactive.push(voices_internal + i);
  }
}
FMVoiceManager::~FMVoiceManager() { delete voices_internal; }