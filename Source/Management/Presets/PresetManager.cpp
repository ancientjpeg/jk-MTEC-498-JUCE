//
//  PresetManager.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//

#include "../Presets/PresetManager.h"
#include "../Folder Manager/FolderManager.h"
#include "../Interface/ProcessorInterface.h"
#include "../Parameters/ParamManager.h"
#include "../Properties/PropertyManager.h"

/* */
PresetManager::PresetManager(ProcessorInterface *inInterface)
    : mProcessorInterface(inInterface)
{
  auto presetsFolder = FolderManager::getPresetsFolder();

  _constructPresetFilesArray();
}

/* */
PresetManager::~PresetManager()
{
  int *i = new int;
  delete i;
}

/* */
void PresetManager::loadPreset(int inListIndex)
{
  auto                              file_to_load = mPresetFiles[inListIndex];

  std::unique_ptr<juce::XmlElement> preset_xml(parseXML(file_to_load));

  juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*preset_xml);
  mProcessorInterface->getParamManager()->getValueTree()->replaceState(
      parameter_tree);
}

/* */
void PresetManager::saveCurrentPreset(juce::String inPresetName)
{
  // Get the underlying ValueTree from out "Parameter Value Tree"
  auto tree_state
      = mProcessorInterface->getParamManager()->getValueTree()->copyState();
  auto prop_state = mProcessorInterface->getPropertyManager();

  // Convert the value tree into an XML object which can be saved on disk to as
  // binary
  auto xml = tree_state.createXml();
  xml->addChildElement(prop_state->createXMLChild().get());

  auto preset_file
      = FolderManager::getPresetsFolder().getChildFile(inPresetName + ".xml");

  if (preset_file.existsAsFile()) {
    preset_file.deleteFile();
  }

  preset_file.appendText(xml->toString());

  _constructPresetFilesArray();
}

juce::StringArray PresetManager::getCurrentPresetNames()
{
  juce::StringArray preset_names;

  for (auto file : mPresetFiles) {
    preset_names.add(file.getFileNameWithoutExtension());
  }

  return preset_names;
}

void PresetManager::_constructPresetFilesArray()
{
  mPresetFiles.clear();

  juce::RangedDirectoryIterator iter(FolderManager::getPresetsFolder(), false,
                                     "*.xml");

  for (auto entry : iter) {
    mPresetFiles.add(entry.getFile());
  }
}
