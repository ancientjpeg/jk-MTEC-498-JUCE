/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
jkClassPlugAudioProcessorEditor::jkClassPlugAudioProcessorEditor(
    jkClassPlugAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(800, 600);
  freqSlider.setSliderStyle(juce::Slider::LinearBarVertical);
  freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 90, 20);
  freqSlider.onValueChange = [this]() {
    audioProcessor.setFreq(freqSlider.getValue());
  };
  freqSlider.setRange(20.f, 20000.f, 0.f);
  freqSlider.setSkewFactorFromMidPoint(2000.f);
  freqSlider.setValue(*p.mFreq);
  addAndMakeVisible(&freqSlider);

  FMFreqSlider.setSliderStyle(juce::Slider::LinearBarVertical);
  FMFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 90, 20);
  FMFreqSlider.onValueChange = [this]() {
    audioProcessor.setFMRatio(FMFreqSlider.getValue());
  };
  FMFreqSlider.setRange(0.25f, 4.f, 0.f);
  FMFreqSlider.setSkewFactorFromMidPoint(1.f);
  FMFreqSlider.setValue(*p.mFMRatio);
  addAndMakeVisible(&FMFreqSlider);

  FMAmtSlider.setSliderStyle(juce::Slider::LinearBarVertical);
  FMAmtSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 90, 20);
  FMAmtSlider.onValueChange = [this]() {
    audioProcessor.setFMAmt(FMAmtSlider.getValue());
  };
  FMAmtSlider.setRange(0.0f, 1.f, 0.f);
  FMAmtSlider.setValue(*p.mFMAmt);
  addAndMakeVisible(&FMAmtSlider);

  muteButton.setButtonText("MUTE TOGGLE");
  muteButton.onClick = [this]() { audioProcessor.muteToggle(); };
  addAndMakeVisible(muteButton);
}

jkClassPlugAudioProcessorEditor::~jkClassPlugAudioProcessorEditor() {}

//==============================================================================
void jkClassPlugAudioProcessorEditor::paint(juce::Graphics &g)
{
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("I am making a sine wave now...", getLocalBounds(),
                   juce::Justification::centred, 1);
}

void jkClassPlugAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  freqSlider.setBounds(40, 0, 80, getHeight() - 20);
  FMFreqSlider.setBounds(120, 0, 80, getHeight() - 20);
  FMAmtSlider.setBounds(200, 0, 80, getHeight() - 20);
  muteButton.setBounds(400, 0, 150, 40);
}
