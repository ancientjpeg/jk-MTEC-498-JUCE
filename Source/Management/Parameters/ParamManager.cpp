/*
  ==============================================================================

    ParamDefines.cpp
    Created: 1 Mar 2022 1:20:32am
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "ParamManager.h"

ParamManager::ParamManager(ProcessorInterface *interface)
    : mInterface(interface), mUndoManager(30000, 200)
{
  mParamState.reset(new juce::AudioProcessorValueTreeState(
      *mInterface->getAudioProcessor(), &mUndoManager, "PARAMETER_STATE",
      getLayout()));
}

juce::AudioProcessorValueTreeState *ParamManager::getValueTree()
{
  return mParamState.get();
}

juce::AudioProcessorValueTreeState::ParameterLayout
ParamManager::generateLayout()
{
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  for (int i = 0; i < NUM_PARAMS; i++) {
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        PARAM_NAMES[i], PARAM_NAMES[i], PARAM_RANGES[i], PARAM_DEFAULTS[i]));
  }
  return layout;
}

float ParamManager::getParamValue(jkClassFloatPluginParams parameterID)
{
  return mParamState->getRawParameterValue(PARAM_NAMES[parameterID])->load();
}

juce::RangedAudioParameter *
ParamManager::getParam(jkClassFloatPluginParams parameterID)
{
  return mParamState->getParameter(PARAM_NAMES[parameterID]);
}