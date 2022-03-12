//
//  PresetManager.h
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//
#ifndef JK_PRESET_MANAGER_H
#define JK_PRESET_MANAGER_H

#include "../Interface/ProcessorInterface.h"

class PresetManager {
public:
  /* */
  PresetManager(ProcessorInterface *inInterface);

  /* */
  ~PresetManager();

  /* */
  void loadPreset(int inListIndex);

  /* */
  juce::StringArray getCurrentPresetNames();

  /* */
  void saveCurrentPreset(juce::String inPresetName);

private:
  /* */
  void                    _constructPresetFilesArray();

  juce::Array<juce::File> mPresetFiles;

  ProcessorInterface     *mProcessorInterface;
};

#endif /* PresetManager_h */
