/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "Sine.h"
#include <JuceHeader.h>

//==============================================================================
/**
 */
class jkClassPlugAudioProcessor : public juce::AudioProcessor {
public:
  //==============================================================================
  jkClassPlugAudioProcessor();
  ~jkClassPlugAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool                        hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool               acceptsMidi() const override;
  bool               producesMidi() const override;
  bool               isMidiEffect() const override;
  double             getTailLengthSeconds() const override;

  //==============================================================================
  int                getNumPrograms() override;
  int                getCurrentProgram() override;
  void               setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;
  void setFreq(float freq);
  void setFMFreq(float freq);
  void muteToggle();

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jkClassPlugAudioProcessor)
  Sine  carrier, modulator;
  float mFMRatio, mRadToTable, mGain;
  bool  mMute;
};
