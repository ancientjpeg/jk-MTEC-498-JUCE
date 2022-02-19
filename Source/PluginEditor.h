/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================
/**
 */
class jkClassPlugAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  jkClassPlugAudioProcessorEditor(jkClassPlugAudioProcessor &);
  ~jkClassPlugAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  jkClassPlugAudioProcessor &audioProcessor;
  juce::Slider               freqSlider, FMFreqSlider, FMAmtSlider, gainSlider;
  juce::TextButton           muteButton;
  juce::AudioProcessorValueTreeState::SliderAttachment frq, fmf, fma, gn;
  juce::AudioProcessorValueTreeState::ButtonAttachment mb;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jkClassPlugAudioProcessorEditor)
};
