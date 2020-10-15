/*
  ==============================================================================

    AnchorControlStrip.cpp
    Created: 7 Oct 2020 11:46:13am
    Author:  Administrator

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnchorControlStrip.h"

//==============================================================================
AnchorControlStrip::AnchorControlStrip(SampleFlexAudioProcessor& p, String anchorNum) : processor(p), anchorNum(anchorNum)
{
	setSize(getLocalBounds().getWidth(), getLocalBounds().getHeight());

	anchorPos.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	anchorPos.setRotaryParameters(4.71225, 7.85375, true);
	anchorPos.setRange(0, 1, .0001f);
	anchorPos.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	anchorPos.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&anchorPos);

	skew.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	skew.setRotaryParameters(4.71225, 7.85375, true);
	skew.setRange(0, 1, .0001f);
	skew.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	skew.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&skew);

	lcr.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	lcr.setRotaryParameters(4.71225, 7.85375, true);
	lcr.setRange(0, 2, 1);
	lcr.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	lcr.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&lcr);

	onOff.setEnabled(true);
	lcr.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	lcr.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&onOff);

	anchorLabel.attachToComponent(&anchorPos, false);
	anchorLabel.setText("Anchor Pos", juce::NotificationType::dontSendNotification);
	anchorLabel.setJustificationType(juce::Justification::centredBottom);

	skewLabel.attachToComponent(&skew, false);
	skewLabel.setText("N/A", juce::NotificationType::dontSendNotification);
	skewLabel.setJustificationType(juce::Justification::centredBottom);

	lcrLabel.attachToComponent(&lcr, false);
	lcrLabel.setText("Anchor Type", juce::NotificationType::dontSendNotification);
	lcrLabel.setJustificationType(juce::Justification::centredBottom);

	onOffLabel.attachToComponent(&onOff, false);
	onOffLabel.setText("on/off toggle", juce::NotificationType::dontSendNotification);
	onOffLabel.setJustificationType(juce::Justification::centredBottom);

	anchorPosAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "ANCHORPOS" + anchorNum, anchorPos);
	lcrAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "LCR" + anchorNum, lcr);
	onOffAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.paramState, "ONOFF" + anchorNum, onOff);

	anchorPos.setComponentID("ANCHORPOS" + anchorNum);
}

AnchorControlStrip::~AnchorControlStrip()
{
}

void AnchorControlStrip::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);
	g.setColour(Colours::white);
	g.setFont(14.0f);
}

void AnchorControlStrip::resized()
{
	juce::Rectangle<int> bounds(getLocalBounds());
	bounds.removeFromTop(25);
	int height = bounds.getHeight();
	anchorPos.setBounds(bounds.removeFromTop(height / 4));
	skew.setBounds(bounds.removeFromTop(height / 4));
	lcr.setBounds(bounds.removeFromTop(height / 4));
	onOff.setBounds(bounds.removeFromTop(height / 4));
}
