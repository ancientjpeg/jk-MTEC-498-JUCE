#ifndef JK_PARAM_MANAGER_H
#define JK_PARAM_MANAGER_H

#include "ParamDefines.h"
#include "ProcessorInterface.h"

class ParamManager {

  ProcessorInterface                                 *mInterface;
  juce::UndoManager                                   mUndoManager;
  std::unique_ptr<juce::AudioProcessorValueTreeState> mParamState;

  juce::AudioProcessorValueTreeState::ParameterLayout generateLayout();

public:
  ParamManager(ProcessorInterface *interface);
  juce::AudioProcessorValueTreeState *getValueTree();
  float ParamManager::getParamValue(jkClassFloatPluginParams parameterID);
  juce::RangedAudioParameter *getParam(jkClassFloatPluginParams parameterID);
};

#endif