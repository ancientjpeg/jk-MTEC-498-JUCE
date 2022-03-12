#ifndef JK_PROCESSOR_INTERFACE_H
#define JK_PROCESSOR_INTERFACE_H

#include "JuceHeader.h"

class ParamManager;
class PresetManager;

class ProcessorInterface {

public:
  virtual ~ProcessorInterface(){};

  virtual ParamManager         *getParameterManager() = 0;

  virtual PresetManager        *getPresetManager()    = 0;

  virtual juce::AudioProcessor *getAudioProcessor()   = 0;
};

#endif