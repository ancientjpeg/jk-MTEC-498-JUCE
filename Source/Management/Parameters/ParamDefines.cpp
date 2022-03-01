/*
  ==============================================================================

    ParamDefines.cpp
    Created: 1 Mar 2022 1:20:32am
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "ParamDefines.h"

juce::AudioProcessorValueTreeState::ParameterLayout getLayout()
{
  using juce::String;
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  for (int i = 0; i < NUM_PARAMS; i++) {
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        PARAM_NAMES[i], PARAM_NAMES[i], PARAM_RANGES[i], PARAM_DEFAULTS[i]));
  }
  return layout;
}