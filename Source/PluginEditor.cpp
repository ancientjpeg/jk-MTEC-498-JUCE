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

  setLookAndFeel(&baseStyle);
  setSize(800, 600);
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
  for (int i = 0; i < PARAM_MUTE; i++) {
    g.drawSingleLineText(PARAM_NAMES[i], mSliders[i]->getX(),
                         mSliders[i]->getBottom() + txtOff);
  }
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
  for (int i = 0; i < PARAM_MUTE; i++) {
    mSliders[i]->setBounds((i + 2) * sep + (i + 1) * sliderWidth, sliderTop,
                           sliderWidth, slHeight);
  }
  mMuteButton->setBounds(5 * sep + 4 * sliderWidth, getHeight() - 40, 200, 40);
}
