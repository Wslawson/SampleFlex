/*
  ==============================================================================

    FilterStrip.cpp
    Created: 7 Oct 2020 11:46:27am
    Author:  Administrator

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterStrip.h"

//==============================================================================
FilterStrip::FilterStrip(SampleFlexAudioProcessor& p) : processor(p)
{
	setSize(getLocalBounds().getWidth(), getLocalBounds().getHeight());

	freq.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	freq.setRotaryParameters(4.71225, 7.85375, true);
	freq.setRange(0, 1, .0001f);
	freq.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	freq.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&freq);

	q.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	q.setRotaryParameters(4.71225, 7.85375, true);
	q.setRange(0, 1, .0001f);
	q.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	q.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&q);

	type.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	type.setRotaryParameters(4.71225, 7.85375, true);
	type.setRange(0, 5, 1);
	type.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	type.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&type);

	drive.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	drive.setRotaryParameters(4.71225, 7.85375, true);
	drive.setRange(0, 1, 0.001);
	drive.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	drive.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&drive);

	freqLabel.attachToComponent(&freq, false);
	freqLabel.setText(" Frequency ", juce::NotificationType::dontSendNotification);
	freqLabel.setJustificationType(juce::Justification::centredBottom);

	qLabel.attachToComponent(&q, false);
	qLabel.setText(" Resonance ", juce::NotificationType::dontSendNotification);
	qLabel.setJustificationType(juce::Justification::centredBottom);

	typeLabel.attachToComponent(&type, false);
	typeLabel.setText(" Type ", juce::NotificationType::dontSendNotification);
	typeLabel.setJustificationType(juce::Justification::centredBottom);

	driveLabel.attachToComponent(&drive, false);
	driveLabel.setText(" Drive ", juce::NotificationType::dontSendNotification);
	driveLabel.setJustificationType(juce::Justification::centredBottom);

	freqAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "FREQ", freq);
	qAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "Q", q);
	typeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "FILTERTYPE", type);
	driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "FILTERDRIVE", drive);
}

FilterStrip::~FilterStrip()
{
}

void FilterStrip::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);
	g.setColour(Colours::white);
	g.setFont(14.0f);
}

void FilterStrip::resized()
{
	juce::Rectangle<int> rect(getLocalBounds());
	rect.removeFromTop(25);
	int height = rect.getHeight();
	freq.setBounds(rect.removeFromTop(height / 4));
	q.setBounds(rect.removeFromTop(height / 4));
	type.setBounds(rect.removeFromTop(height / 4));
	drive.setBounds(rect.removeFromTop(height / 4));
	repaint();
}
