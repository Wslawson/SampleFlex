/*
  ==============================================================================

    ADSRStrip.cpp
    Created: 14 Oct 2020 7:43:06pm
    Author:  Administrator

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ADSRStrip.h"

//==============================================================================
ADSRStrip::ADSRStrip( SampleFlexAudioProcessor& p) : processor(p)
{
	setSize( getLocalBounds().getWidth(), getLocalBounds().getWidth() );

	attackSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	attackSelector.setRotaryParameters(4.71225, 7.85375, true);
	attackSelector.setRange(0, 5, 0.001);
	attackSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	attackSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&attackSelector);

	decaySelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	decaySelector.setRotaryParameters(4.71225, 7.85375, true);
	decaySelector.setRange(0, 5, 0.001);
	decaySelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	decaySelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&decaySelector);

	sustainSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	sustainSelector.setRotaryParameters(4.71225, 7.85375, true);
	sustainSelector.setRange(0, 5, 0.001);
	sustainSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	sustainSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&sustainSelector);

	releaseSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	releaseSelector.setRotaryParameters(4.71225, 7.85375, true);
	releaseSelector.setRange(0, 5, 0.001);
	releaseSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	releaseSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&releaseSelector);

	attackLabel.attachToComponent(&attackSelector, false);
	attackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
	attackLabel.setJustificationType(juce::Justification::centredBottom);

	decayLabel.attachToComponent(&decaySelector, false);
	decayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
	decayLabel.setJustificationType(juce::Justification::centredBottom);

	sustainLabel.attachToComponent(&sustainSelector, false);
	sustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
	sustainLabel.setJustificationType(juce::Justification::centredBottom);

	releaseLabel.attachToComponent(&releaseSelector, false);
	releaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
	releaseLabel.setJustificationType(juce::Justification::centredBottom);

	addAndMakeVisible(&attackLabel);
	addAndMakeVisible(&decayLabel);
	addAndMakeVisible(&sustainLabel);
	addAndMakeVisible(&releaseLabel);

	attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "ATTACK", attackSelector);
	decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "DECAY", decaySelector);
	sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "SUSTAIN", sustainSelector);
	releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "RELEASE", releaseSelector);
}

ADSRStrip::~ADSRStrip()
{
}

void ADSRStrip::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (Colours::grey);
    // g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (Colours::white);
    // g.setFont (14.0f);
    // g.drawText ("ADSRStrip", getLocalBounds(),
    //            Justification::centred, true);   // draw some placeholder text
}

void ADSRStrip::resized()
{
	auto width = getWidth() ;
	auto height = getHeight();
	Rectangle<int> rect = getLocalBounds();
	rect.removeFromTop(20);
	attackSelector.setBounds(rect.removeFromLeft(width / 4));
	decaySelector.setBounds(rect.removeFromLeft(width / 4 ));
	sustainSelector.setBounds(rect.removeFromLeft(width / 4));
	releaseSelector.setBounds(rect.removeFromLeft(width / 4));
}
