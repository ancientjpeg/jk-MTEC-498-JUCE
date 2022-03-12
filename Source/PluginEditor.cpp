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
  setLookAndFeel(&baseStyle);

  for (int i = 0; i < PARAM_MUTE; i++) {
    jkClassSliderBase *slider = new jkClassSliderBase();
    mSliders.add(slider);
    ATTACHMENT_T *at = new ATTACHMENT_T(*p.getParamManager()->getValueTree(),
                                        PARAM_NAMES[i], *slider);
    mAttachments.add(at);
    addAndMakeVisible(mSliders[i]);
  }

  mSliders[PARAM_FM_RATIO]->setSkewFactorFromMidPoint(1.f);

  mSliders[PARAM_DELAY_TIME]->setSkewFactorFromMidPoint(1.f);

  /* MAKE BUTTON DEFINES !!! */
  mMuteButton.reset(new juce::TextButton());
  mMuteButton->setClickingTogglesState(true);
  mb.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(
      *p.getParamManager()->getValueTree(), PARAM_NAMES[PARAM_MUTE],
      *mMuteButton));
  addAndMakeVisible(*mMuteButton);
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
  g.drawSingleLineText(PARAM_NAMES[PARAM_FM_RATIO],
                       mSliders[PARAM_FM_RATIO]->getX(),
                       mSliders[PARAM_FM_AMT]->getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_FM_AMT],
                       mSliders[PARAM_FM_AMT]->getX(),
                       mSliders[PARAM_FM_AMT]->getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_DELAY_TIME],
                       mSliders[PARAM_DELAY_TIME]->getX(),
                       mSliders[PARAM_DELAY_TIME]->getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_DELAY_FEEDBACK],
                       mSliders[PARAM_DELAY_FEEDBACK]->getX() - 6,
                       mSliders[PARAM_DELAY_FEEDBACK]->getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_DELAY_MIX],
                       mSliders[PARAM_DELAY_MIX]->getX(),
                       mSliders[PARAM_DELAY_MIX]->getBottom() + txtOff);
  g.drawSingleLineText(PARAM_NAMES[PARAM_GAIN], mSliders[PARAM_GAIN]->getX(),
                       mSliders[PARAM_GAIN]->getBottom() + txtOff);
}
void jkClassPlugAudioProcessorEditor::paintOverChildren(juce::Graphics &g)
{
  g.setFont(juce::Font(12, juce::Font::italic));
  g.drawSingleLineText(PARAM_NAMES[PARAM_MUTE],
                       mMuteButton->getRight() - mMuteButton->getWidth() / 2
                           - 12,
                       mMuteButton->getBottom() - mMuteButton->getHeight() / 2);
}

void jkClassPlugAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  int sliderWidth = 60, sep = 15, slHeight = getHeight() - 80;
  int sliderTop = 15;
  mSliders[PARAM_FM_RATIO]->setBounds(2 * sep + sliderWidth, sliderTop,
                                      sliderWidth, slHeight);
  mSliders[PARAM_FM_AMT]->setBounds(3 * sep + 2 * sliderWidth, sliderTop,
                                    sliderWidth, slHeight);
  mSliders[PARAM_DELAY_TIME]->setBounds(4 * sep + 3 * sliderWidth, sliderTop,
                                        sliderWidth, slHeight);
  mSliders[PARAM_DELAY_FEEDBACK]->setBounds(5 * sep + 4 * sliderWidth,
                                            sliderTop, sliderWidth, slHeight);
  mSliders[PARAM_DELAY_MIX]->setBounds(6 * sep + 5 * sliderWidth, sliderTop,
                                       sliderWidth, slHeight);
  mSliders[PARAM_GAIN]->setBounds(7 * sep + 6 * sliderWidth, sliderTop,
                                  sliderWidth, slHeight);
  mMuteButton->setBounds(5 * sep + 4 * sliderWidth, getHeight() - 40, 200, 40);
}
