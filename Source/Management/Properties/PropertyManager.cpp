#include "PropertyManager.h"
#include "../Presets/PresetManager.h"

PropertyManager::PropertyManager(ProcessorInterface *interface)
    : mInterface(interface),
mPropertyTree("Properties", {}, {{"PresetNames", {}, {}}})
{
//
  auto presetNames
      = mInterface->getPresetManager()->getCurrentPresetNames();
  auto presetNameTree = mPropertyTree.getChildWithName("PresetNames");
  for (juce::String s : presetNames) {
    DBG(s);
    presetNameTree.appendChild({s, {}, {}}, nullptr);
  }
}
juce::ValueTree *PropertyManager::getValueTree()
{
  // This is unused at the moment
  return &mPropertyTree;
}
