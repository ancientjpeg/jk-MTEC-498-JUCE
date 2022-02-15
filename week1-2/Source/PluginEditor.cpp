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
  freqSlider.setRange(20., 20000., 0.0);
  freqSlider.setSkewFactorFromMidPoint(2000.);
  freqSlider.setValue(880.);
  freqSlider.onValueChange = [this]() {
    audioProcessor.setFreq(freqSlider.getValue());
  };
  freqSlider.addListener(this);
  addAndMakeVisible(&freqSlider);

  muteButton.setButtonText("MUTE TOGGLE");
  muteButton.addListener(this);
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
  freqSlider.setBounds(50, 0, 80, getHeight() - 20);
  muteButton.setBounds(400, 0, 150, 40);
}

void jkClassPlugAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
  // if (slider == &freqSlider) {
  //   audioProcessor.setFreq(freqSlider.getValue());
  // }
}
void jkClassPlugAudioProcessorEditor::buttonClicked(juce::Button *button)
{
  // if (button == &muteButton) {
  //   audioProcessor.muteToggle();
  // }
}
