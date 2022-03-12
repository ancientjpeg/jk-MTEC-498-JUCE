#ifndef JK_PARAM_MANAGER_H
#define JK_PARAM_MANAGER_H

#include "ParamDefines.h"
#include "../Interface/ProcessorInterface.h"


class ParamManager {

  ProcessorInterface                                 *mInterface;
  juce::UndoManager                                   mUndoManager;
  std::unique_ptr<juce::AudioProcessorValueTreeState> mParamState;

  juce::AudioProcessorValueTreeState::ParameterLayout generateLayout();

public:
  ParamManager(ProcessorInterface *interface);
  juce::AudioProcessorValueTreeState *getValueTree();
  float getParamValue(jkClassFloatPluginParams parameterID);
  juce::RangedAudioParameter *getParam(jkClassFloatPluginParams parameterID);
  void setParam(jkClassFloatPluginParams parameterID, float val);
};

#endif
