#ifndef JK_PARAM_MANAGER_H
#define JK_PARAM_MANAGER_H

#include "ParamDefines.h"
#define LAYOUT_T juce::AudioProcessorValueTreeState::ParameterLayout
class ParamManager {
public:
  ParamManager();
  LAYOUT_T getLayout();
};

#endif