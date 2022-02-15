#ifndef PARAM_DEFINES_H
#define PARAM_DEFINES_H

#include <JuceHeader.h>

enum jkClassFloatPluginParams {
  PARAM_FREQ,
  PARAM_FM_RATIO,
  PARAM_FM_AMT,
  PARAM_GAIN,
};

juce::AudioProcessorValueTreeState::ParameterLayout getLayout();

#endif
