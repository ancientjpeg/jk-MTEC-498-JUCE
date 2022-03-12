//
//  MKUFolderManager.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//

#include "FolderManager.h"

FolderManager::FolderManager() {}

FolderManager::~FolderManager() {}

juce::File FolderManager::getRootFolder()
{
  auto       osType = juce::SystemStats::getOperatingSystemType();
  juce::File folder;

  if ((osType & juce::SystemStats::MacOSX) != 0) {

    folder = juce::File("/Library/Application Support/MTEC_PLUGS/");
  }
  else if ((osType & juce::SystemStats::Windows) != 0) {

    folder = juce::File::getSpecialLocation(
                 juce::File::commonApplicationDataDirectory)
                 .getChildFile("MTEC_PLUGS");
  }

  folder.getParentDirectory().setReadOnly(false);

  if (!folder.exists()) {
    DBG("Created Root Folder " + folder.createDirectory().getErrorMessage());
  }

  return folder;
}

juce::File FolderManager::getAppFolder()
{
#ifndef JucePlugin_Name
#define JucePlugin_Name "Intellisense go Away"
#endif
  juce::File productAppFolder = getRootFolder().getChildFile(JucePlugin_Name);

  if (!productAppFolder.exists()) {
    DBG("Created Product Folder "
        + productAppFolder.createDirectory().getErrorMessage());
  }

  return productAppFolder;
}

juce::File FolderManager::getPresetsFolder()
{
  juce::File presetsFolder = getAppFolder().getChildFile("Presets");

  if (!presetsFolder.exists()) {
    DBG("Created Preset Folder "
        + presetsFolder.createDirectory().getErrorMessage());
  }

  return presetsFolder;
}
