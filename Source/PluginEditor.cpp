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
      fmf(p.mParamState, "FM Ratio", FMFreqSlider),
      fma(p.mParamState, "FM Amount", FMAmtSlider),
      dt(p.mParamState, "Delay Time", mDelayTimeSlider),
      dfb(p.mParamState, "Delay Feedback", mDelayFBSlider),
      dm(p.mParamState, "Delay Mix", mDelayMixSlider),
      gn(p.mParamState, "Gain", gainSlider),
      mb(p.mParamState, "Mute", muteButton)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(800, 600);
  setLookAndFeel(&baseStyle);

  FMFreqSlider.setSkewFactorFromMidPoint(1.f);
  addAndMakeVisible(FMFreqSlider);
  addAndMakeVisible(FMAmtSlider);

  addAndMakeVisible(mDelayTimeSlider);
  addAndMakeVisible(mDelayFBSlider);
  addAndMakeVisible(mDelayMixSlider);

  addAndMakeVisible(gainSlider);
  muteButton.setClickingTogglesState(true);
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

  g.setFont(juce::Font(12, juce::Font::italic));
  int txtOff = 12;
  g.drawSingleLineText(PARAM_NAMES[PARAM_FM_RATIO], FMFreqSlider.getX(),
                       FMFreqSlider.getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_FM_AMT], FMAmtSlider.getX(),
                       FMAmtSlider.getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_DELAY_TIME], mDelayTimeSlider.getX(),
                       mDelayTimeSlider.getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_DELAY_FEEDBACK],
                       mDelayFBSlider.getX() - 6,
                       mDelayFBSlider.getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_DELAY_MIX], mDelayMixSlider.getX(),
                       mDelayMixSlider.getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_GAIN], gainSlider.getX(),
                       gainSlider.getBottom() + txtOff);
}
void jkClassPlugAudioProcessorEditor::paintOverChildren(juce::Graphics &g)
{
  g.setFont(juce::Font(12, juce::Font::italic));
  g.drawSingleLineText(PARAM_NAMES[PARAM_MUTE],
                       muteButton.getRight() - muteButton.getWidth() / 2 - 12,
                       muteButton.getBottom() - muteButton.getHeight() / 2);
}

void jkClassPlugAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  int sliderWidth = 60, sep = 15, slHeight = getHeight() - 80;
  int sliderTop = 15;
  FMFreqSlider.setBounds(2 * sep + sliderWidth, sliderTop, sliderWidth,
                         slHeight);
  FMAmtSlider.setBounds(3 * sep + 2 * sliderWidth, sliderTop, sliderWidth,
                        slHeight);
  mDelayTimeSlider.setBounds(4 * sep + 3 * sliderWidth, sliderTop, sliderWidth,
                             slHeight);
  mDelayFBSlider.setBounds(5 * sep + 4 * sliderWidth, sliderTop, sliderWidth,
                           slHeight);
  mDelayMixSlider.setBounds(6 * sep + 5 * sliderWidth, sliderTop, sliderWidth,
                            slHeight);
  gainSlider.setBounds(7 * sep + 6 * sliderWidth, sliderTop, sliderWidth,
                       slHeight);
  muteButton.setBounds(5 * sep + 4 * sliderWidth, getHeight() - 40, 200, 40);
}
