/*
  ==============================================================================

    ParamDefines.cpp
    Created: 15 Feb 2022 11:42:06am
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "ParamDefines.h"

juce::AudioProcessorValueTreeState::ParameterLayout getLayout()
{
  using juce::String;
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      String("freq"), String("freq"),
      juce::NormalisableRange<float>(20.f, 20000.f), 880.f));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      String("FMRatio"), String("FM ratio"),
      juce::NormalisableRange<float>(0.25f, 4.f), 2.f));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      String("FMAmt"), String("FM amount"),
      juce::NormalisableRange<float>(0.f, 1.f), 1.f));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      String("gain"), String("gain"), juce::NormalisableRange<float>(0.f, 1.f),
      1.f));
  layout.add(std::make_unique<juce::AudioParameterBool>(String("mute"),
                                                        String("mute"), true));
  return layout;
}
