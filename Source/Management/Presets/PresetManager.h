#ifndef JK_PRESET_MANAGER_H
#define JK_PRESET_MANAGER_H

#include "ProcessorInterface.h"
class PresetManager {
  ProcessorInterface *mInterface;

public:
  PresetManager(ProcessorInterface *interface);
};
#endif