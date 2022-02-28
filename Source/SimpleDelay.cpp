/*
  ==============================================================================

    SimpleDelay.cpp
    Created: 28 Feb 2022 2:29:22pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "SimpleDelay.h"

SimpleDelay::SimpleDelay(float maxSeconds, float sampleRate)
    : cbuff(std::ceil(maxSeconds * sampleRate))
{
}