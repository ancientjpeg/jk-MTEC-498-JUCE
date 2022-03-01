#ifndef PARAM_DEFINES_H
#define PARAM_DEFINES_H

#include <JuceHeader.h>

enum jkClassFloatPluginParams {
  PARAM_FREQ,
  PARAM_FM_RATIO,
  PARAM_FM_AMT,
  PARAM_GAIN,
};

juce::AudioProcessorValueTreeState::ParameterLayout getLayout()
{
  using juce::String;
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
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

#endif
