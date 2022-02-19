/*
  ==============================================================================

    jkClassSliderBase.h
    Created: 19 Feb 2022 12:55:22am
    Author:  Jackson Kaplan

  ==============================================================================
*/

#ifndef JK_CLASS_SLIDER_BASE_H
#define JK_CLASS_SLIDER_BASE_H

#include <JuceHeader.h>
class jkClassSliderBase : public juce::Slider {

public:
  jkClassSliderBase()
  {
    setSliderStyle(juce::Slider::LinearVertical);
    setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 40);
    setColour(juce::Slider::ColourIds::backgroundColourId,
              juce::Colours::lightgrey);
    setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    setColour(juce::Slider::ColourIds::textBoxTextColourId,
              juce::Colours::black);
  }
};

#endif