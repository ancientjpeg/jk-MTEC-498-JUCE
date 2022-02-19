/*
  ==============================================================================

    jkStyle.h
    Created: 19 Feb 2022 1:04:51am
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class jkStyle : public juce::LookAndFeel_V4 {
public:
  jkStyle()
  {
    using juce::LookAndFeel_V4;
    ColourScheme scheme(
        juce::Colours::white, juce::Colours::white, juce::Colours::white,
        juce::Colours::black, juce::Colours::black, juce::Colours::white,
        juce::Colours::black, juce::Colours::yellow, juce::Colours::black);
    setColourScheme(scheme);
    setColour(juce::Slider::ColourIds::backgroundColourId,
              juce::Colours::white);
    setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jkStyle)
};
