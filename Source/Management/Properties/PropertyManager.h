#ifndef JK_PROPERTY_MANAGER_H
#define JK_PROPERTY_MANAGER_H

#include "../Interface/ProcessorInterface.h"
#include "../Presets/PresetManager.h"

class jkClassAudioProcessor;
class PropertyManager {
  ProcessorInterface *mInterface;
  juce::ValueTree               mPropertyTree;

public:
  PropertyManager(ProcessorInterface *interface);
  juce::ValueTree *getValueTree();
  
};

#endif
