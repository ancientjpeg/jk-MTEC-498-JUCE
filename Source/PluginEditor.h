/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "jkClassSliderBase.h"
#include "jkStyle.h"
#include <JuceHeader.h>

#define ATTACHMENT_T juce::AudioProcessorValueTreeState::SliderAttachment

class jkClassPlugAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  jkClassPlugAudioProcessorEditor(jkClassPlugAudioProcessor &);
  ~jkClassPlugAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void paintOverChildren(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  jkClassPlugAudioProcessor          &audioProcessor;
  juce::OwnedArray<jkClassSliderBase> mSliders;
  std::unique_ptr<juce::TextButton>   mMuteButton;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> mb;
  juce::OwnedArray<ATTACHMENT_T> mAttachments;
  jkStyle                        baseStyle;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jkClassPlugAudioProcessorEditor)
};
