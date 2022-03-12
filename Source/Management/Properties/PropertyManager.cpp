#include "PropertyManager.h"
#include "../Presets/PresetManager.h"

PropertyManager::PropertyManager(ProcessorInterface *interface)
    : mInterface(interface)
{
  auto presetNames = mInterface->getPresetManager()->getCurrentPresetNames();
  for (juce::String s : presetNames) {
    DBG(s);
  }
}
std::unique_ptr<juce::XmlElement> PropertyManager::createXMLChild()
{
  auto xml = std::make_unique<juce::XmlElement>("Properties");
  xml->setAttribute("Property1", "This is a property");
  return xml;
}
