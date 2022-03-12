/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
jkClassPlugAudioProcessor::jkClassPlugAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
        BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
            ),
#else
    :
#endif
      mParamManager(this), mPresetManager(this), mPropertyManager(this),
      mVoices(8, getParamManager()->getParamValue(PARAM_FM_RATIO),
              getParamManager()->getParamValue(PARAM_FM_AMT))
{
  mMidiState.addListener(&mVoices);
}

jkClassPlugAudioProcessor::~jkClassPlugAudioProcessor() {}

//==============================================================================
const juce::String jkClassPlugAudioProcessor::getName() const
{
#ifndef JucePlugin_Name
#define JucePlugin_Name "VSCode please stop"
#endif
  return JucePlugin_Name;
}

bool jkClassPlugAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool jkClassPlugAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool jkClassPlugAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double jkClassPlugAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int    jkClassPlugAudioProcessor::getNumPrograms()
{
  return 1; // NB: some hosts don't cope very well if you tell
            // them there are 0 programs, so this should be at
            // least 1, even if you're not really implementing
            // programs.
}

int                jkClassPlugAudioProcessor::getCurrentProgram() { return 0; }

void               jkClassPlugAudioProcessor::setCurrentProgram(int index) {}

const juce::String jkClassPlugAudioProcessor::getProgramName(int index)
{
  return {};
}

void jkClassPlugAudioProcessor::changeProgramName(int                 index,
                                                  const juce::String &newName)
{
}

//==============================================================================
void jkClassPlugAudioProcessor::prepareToPlay(double sampleRate,
                                              int    samplesPerBlock)
{
  mTwoPiSampleDeltaT = (1.f / sampleRate) * 2.f * M_PI;
  if (!mDelay.isPrepared) {
    mDelay.prepare(getParamManager()->getParamValue(PARAM_DELAY_TIME),
                   getParamManager()->getParamValue(PARAM_DELAY_FEEDBACK),
                   getParamManager()->getParamValue(PARAM_DELAY_MIX), 5.f,
                   sampleRate, 2);
  }
}

void jkClassPlugAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool jkClassPlugAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is
  // supported. In this template code we only support mono or
  // stereo. Some plugin hosts, such as certain GarageBand
  // versions, will only load plugins that support stereo bus
  // layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
      && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output
    // layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void jkClassPlugAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages)
{
  juce::ScopedNoDenormals noDenormals;
  auto                    totalNumOutputChannels = getTotalNumOutputChannels();

  float                 **channelPtrs = buffer.getArrayOfWritePointers();
  int                     numSamps    = buffer.getNumSamples();
  mMidiState.processNextMidiBuffer(midiMessages, 0, numSamps, false);

  /* check params */
  mVoices.setRatio(getParamManager()->getParamValue(PARAM_FM_RATIO));
  mVoices.setAmt(getParamManager()->getParamValue(PARAM_FM_AMT));
  mDelay.setParams(getParamManager()->getParamValue(PARAM_DELAY_TIME),
                   getParamManager()->getParamValue(PARAM_DELAY_FEEDBACK),
                   getParamManager()->getParamValue(PARAM_DELAY_MIX));
  float gain = getParamManager()->getParamValue(PARAM_GAIN);

  /* process */
  for (int i = 0; i < numSamps; i++) {
    float valueCalc = mVoices.cycle(mTwoPiSampleDeltaT);
    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
      channelPtrs[channel][i] = valueCalc * gain;
    }
  }
  mDelay.processBlocks(channelPtrs, 2, numSamps);
  //
  /* check mute */
  float mute = getParamManager()->getParamValue(PARAM_MUTE);
  if (mute > .5f) {
    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
      std::memset(channelPtrs[channel], 0, sizeof(float) * numSamps);
    }
  }
}

juce::AudioProcessor *jkClassPlugAudioProcessor::getAudioProcessor()
{
  return this;
}
ParamManager *jkClassPlugAudioProcessor::getParamManager()
{
  return &mParamManager;
}
PresetManager *jkClassPlugAudioProcessor::getPresetManager()
{
  return &mPresetManager;
}
PropertyManager *jkClassPlugAudioProcessor::getPropertyManager()
{
  return &mPropertyManager;
}

//==============================================================================
bool jkClassPlugAudioProcessor::hasEditor() const
{
  return true; // (change this to false if you choose to not
               // supply an editor)
}

juce::AudioProcessorEditor *jkClassPlugAudioProcessor::createEditor()
{
  return new jkClassPlugAudioProcessorEditor(*this);
}

//==============================================================================
void jkClassPlugAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
  // You should use this method to store your parameters in
  // the memory block. You could do that either as raw data,
  // or use the XML or ValueTree classes as intermediaries to
  // make it easy to save and load complex data.
}

void jkClassPlugAudioProcessor::setStateInformation(const void *data,
                                                    int         sizeInBytes)
{
  // You should use this method to restore your parameters
  // from this memory block, whose contents will have been
  // created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
  return new jkClassPlugAudioProcessor();
}
