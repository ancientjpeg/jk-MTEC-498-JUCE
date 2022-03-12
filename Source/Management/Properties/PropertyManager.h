#ifndef JK_PROPERTY_MANAGER_H
#define JK_PROPERTY_MANAGER_H

#include "../Interface/ProcessorInterface.h"
#include "../Presets/PresetManager.h"

class jkClassAudioProcessor;
class PropertyManager {
  ProcessorInterface *mInterface;

public:
  PropertyManager(ProcessorInterface *interface);
  std::unique_ptr<juce::XmlElement> createXMLChild();
};

#endif
