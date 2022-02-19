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
    : AudioProcessorEditor(&p), audioProcessor(p),
      frq(p.mParamState, "freq", freqSlider),
      fmf(p.mParamState, "FMRatio", FMFreqSlider),
      fma(p.mParamState, "FMAmt", FMAmtSlider),
      gn(p.mParamState, "gain", gainSlider),
      mb(p.mParamState, "mute", muteButton)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(800, 600);
  setLookAndFeel(&baseStyle);

  freqSlider.onValueChange = [this]() {
    audioProcessor.setFreq(freqSlider.getValue());
  };
  freqSlider.setRange(20.f, 20000.f, 0.f);
  freqSlider.setSkewFactorFromMidPoint(2000.f);
  freqSlider.setValue(*p.mFreq);
  freqSlider.setTextValueSuffix(" Freq");
  addAndMakeVisible(&freqSlider);

  FMFreqSlider.onValueChange = [this]() {
    audioProcessor.setFMRatio(FMFreqSlider.getValue());
  };
  FMFreqSlider.setRange(0.25f, 4.f, 0.f);
  FMFreqSlider.setSkewFactorFromMidPoint(1.f);
  FMFreqSlider.setValue(*p.mFMRatio);
  freqSlider.setTextValueSuffix(" FM Ratio");
  addAndMakeVisible(&FMFreqSlider);

  FMAmtSlider.onValueChange = [this]() {
    audioProcessor.setFMAmt(FMAmtSlider.getValue());
  };
  FMAmtSlider.setRange(0.0f, 1.f, 0.f);
  FMAmtSlider.setValue(*p.mFMAmt);
  freqSlider.setTextValueSuffix(" FM Amt");
  addAndMakeVisible(&FMAmtSlider);

  gainSlider.onValueChange = [this]() {
    audioProcessor.setGain(gainSlider.getValue());
  };
  gainSlider.setRange(0.f, 1.f, 0.f);
  gainSlider.setValue(*p.mGain);
  freqSlider.setTextValueSuffix(" Gain");
  addAndMakeVisible(gainSlider);

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
}

void jkClassPlugAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  int sliderWidth = 100, sep = 25, slHeight = getHeight() - 80;
  freqSlider.setBounds(sep, 0, sliderWidth, slHeight);
  FMFreqSlider.setBounds(2 * sep + sliderWidth, 0, sliderWidth, slHeight);
  FMAmtSlider.setBounds(3 * sep + 2 * sliderWidth, 0, sliderWidth, slHeight);
  gainSlider.setBounds(4 * sep + 3 * sliderWidth, 0, sliderWidth, slHeight);
  muteButton.setBounds(5 * sep + 4 * sliderWidth, 0, 200, 40);
}
