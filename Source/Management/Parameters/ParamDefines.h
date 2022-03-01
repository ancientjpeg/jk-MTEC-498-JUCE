#ifndef PARAM_DEFINES_H
#define PARAM_DEFINES_H

#include <JuceHeader.h>

enum jkClassFloatPluginParams {
  PARAM_FM_RATIO,
  PARAM_FM_AMT,
  PARAM_DELAY_TIME,
  PARAM_DELAY_FEEDBACK,
  PARAM_DELAY_MIX,
  PARAM_GAIN,
  PARAM_MUTE,
  NUM_PARAMS,
};

static const juce::StringArray PARAM_NAMES{
    "FM Ratio",  "FM Amount", "Delay Time", "Delay Feedback",
    "Delay Mix", "Gain",      "Mute"};

static const juce::Array<juce::NormalisableRange<float>> PARAM_RANGES{
    // FM
    juce::NormalisableRange<float>(0.25f, 4.f),
    juce::NormalisableRange<float>(0.f, 1.f),
    // Delay
    juce::NormalisableRange<float>(0.001f, 5.f),
    juce::NormalisableRange<float>(0.f, .8f),
    juce::NormalisableRange<float>(0.f, 1.f),
    // Global
    juce::NormalisableRange<float>(0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 1.f)};

juce::AudioProcessorValueTreeState::ParameterLayout getLayout()
{
  using juce::String;
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  for (int i = 0; i < NUM_PARAMS; i++) {
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        PARAM_NAMES[i], PARAM_NAMES[i], PARAM_RANGES[i], 0.f));
  }
  return layout;
}

#endif
