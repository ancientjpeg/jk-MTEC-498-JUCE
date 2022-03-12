#ifndef JK_PROPERTY_MANAGER_H
#define JK_PROPERTY_MANAGER_H

#include "ProcessorInterface.h"

class jkClassAudioProcessor;
class PropertyManager : public ProcessorInterface {

public:
  PropertyManager(ProcessorInterface &interface);
};

#endif