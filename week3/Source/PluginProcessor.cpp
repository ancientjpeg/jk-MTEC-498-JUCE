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
      )
#endif
{
  mWavetable  = juce::AudioBuffer<float>(1, 2048);
  auto *write = mWavetable.getWritePointer(0);
  for (int i = 0; i < mWavetable.getNumSamples(); i++) {
    float currentRad = ((float)i / mWavetable.getNumSamples()) * 2.f * M_PI;
    write[i]         = std::sin(currentRad);
  }
  mFreq    = 880.f;
  mPhase   = 0.f;
  mFMFreq  = 880.f;
  mFMPhase = 0.f;
  mGain    = 0.5f;
  mMute    = true;
}

jkClassPlugAudioProcessor::~jkClassPlugAudioProcessor() {}

//==============================================================================
const juce::String jkClassPlugAudioProcessor::getName() const
{
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
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs, so this should be at least 1, even if you're not really
            // implementing programs.
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
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  mDeltaTime      = 1.f / sampleRate;
  mDeltaTimeTwoPi = mDeltaTime * 2.f * M_PI;
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
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
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
  auto                    totalNumInputChannels  = getTotalNumInputChannels();
  auto                    totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  auto tableRead   = mWavetable.getReadPointer(0);
  auto channelPtrs = buffer.getArrayOfWritePointers();
  for (int i = 0; i < buffer.getNumSamples(); i++) {
    float        currentTable = (mPhase * mRadToTable);
    float        valueCalc;
    unsigned int indexLow = static_cast<unsigned int>(currentTable);
    unsigned int indexHigh =
        indexLow + 1 >= mWavetable.getNumSamples() ? 0 : currentTable + 1;
    float mod = currentTable - indexLow;
    float y0  = tableRead[indexLow];
    float y1  = tableRead[indexHigh];
    valueCalc = (y1 - y0) * mod + y0;
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
      channelPtrs[channel][i] = mMute ? 0.f : valueCalc * mGain;
    }
    mPhase += mFreq * mDeltaTimeTwoPi + fmFreq;
    if (mPhase >= 2.f * M_PI) {
      mPhase = std::fmod(mPhase, 2.f * M_PI);
    }
  }
}

void jkClassPlugAudioProcessor::setFreq(float freq) { mFreq = freq; }
void jkClassPlugAudioProcessor::setFMFreq(float freq) { mFMFreq = freq; }
void jkClassPlugAudioProcessor::muteToggle() { mMute = !mMute; }

//==============================================================================
bool jkClassPlugAudioProcessor::hasEditor() const
{
  return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *jkClassPlugAudioProcessor::createEditor()
{
  return new jkClassPlugAudioProcessorEditor(*this);
}

//==============================================================================
void jkClassPlugAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void jkClassPlugAudioProcessor::setStateInformation(const void *data,
                                                    int         sizeInBytes)
{
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
  return new jkClassPlugAudioProcessor();
}
