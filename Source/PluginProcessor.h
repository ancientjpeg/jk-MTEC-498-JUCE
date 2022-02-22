/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "FMVoice.h"
#include "ParamDefines.h"
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

  //=====================       PUBLIC MEMBERS ============================
  juce::UndoManager                  mUndoManager;
  juce::AudioProcessorValueTreeState mParamState;
  std::atomic<float>                *mFreq, *mFMAmt, *mFMRatio, *mGain, *mMute;
  void                               setFreq(float freq);
  void                               setFMRatio(float ratio);
  void                               setFMAmt(float amt);
  void                               setGain(float gain);
  void                               muteToggle();

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  //==============================================================================
  void                    setModFreq();
  juce::MidiKeyboardState mMidiState;
  FMVoiceManager          mVoices;
  float                   mTwoPiSampleDeltaT;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jkClassPlugAudioProcessor)
};
