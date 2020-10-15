/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SampleFlexAudioProcessorEditor::SampleFlexAudioProcessorEditor (SampleFlexAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),  anchorControlPanel(p), filterStrip(p), 
	sampleWavBox(p, anchorControlPanel), spec(p), adsrStrip(p)
{
    setSize (1150, 850);
	formatManager.registerBasicFormats();

	openSampleButton.setButtonText("Open sample...");
	openSampleButton.onClick = [this] { openSampleButtonClicked(); };

	multiplierSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	multiplierSelector.setRotaryParameters(4.71225f, 7.85375f, true);
	multiplierSelector.setRange(0, 8, 1);
	multiplierSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	multiplierSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&multiplierSelector);

	rampSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	rampSelector.setRotaryParameters(4.71225f, 7.85375f, true);
	rampSelector.setRange(0.0f, 0.5f, 0.01f);
	rampSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	rampSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&rampSelector);

	thickenSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	thickenSelector.setRotaryParameters(4.71225f, 7.85375f, true);
	thickenSelector.setRange(0.85f, 1.15f, 0.0001f);
	thickenSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	thickenSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&thickenSelector);

	gainSelector.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	gainSelector.setRotaryParameters(4.71225f, 7.85375f, true);
	gainSelector.setRange(0, .8, 0.001);
	gainSelector.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
	gainSelector.setPopupDisplayEnabled(true, false, this);
	addAndMakeVisible(&gainSelector);

	gainLabel.attachToComponent(&gainSelector, false);
	gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
	gainLabel.setJustificationType(juce::Justification::centredBottom);

	multiplierLabel.attachToComponent(&multiplierSelector, false);
	multiplierLabel.setText("Multiplier", juce::NotificationType::dontSendNotification);
	multiplierLabel.setJustificationType(juce::Justification::centredBottom);

	rampLabel.attachToComponent(&rampSelector, false);
	rampLabel.setText("Ramp/Smoothing", juce::NotificationType::dontSendNotification);
	rampLabel.setJustificationType(juce::Justification::centredBottom);

	thickenLabel.attachToComponent(&thickenSelector, false);
	thickenLabel.setText("Thicken Amt", juce::NotificationType::dontSendNotification);
	thickenLabel.setJustificationType(juce::Justification::centredBottom);

	addAndMakeVisible(&sampleWavBox);
	addAndMakeVisible(&anchorControlPanel);
	addAndMakeVisible(&openSampleButton);
	addAndMakeVisible(&filterStrip);
	addAndMakeVisible(&spec);
	addAndMakeVisible(&adsrStrip);

	multiplierAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "MULTIPLIER", multiplierSelector);
	gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "GAIN", gainSelector);
	rampAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "RAMP", rampSelector);
	thickenAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.paramState, "THICKEN", thickenSelector);
}

SampleFlexAudioProcessorEditor::~SampleFlexAudioProcessorEditor()
{
}

void SampleFlexAudioProcessorEditor::openSampleButtonClicked()
{	
	processor.suspendProcessing(true);

	juce::FileChooser fileChooser("Select .wav file", {}, "*.wav");
	if (fileChooser.browseForFileToOpen())
	{
		juce::File file = fileChooser.getResult();
		loadSample( file );
	}
	processor.suspendProcessing(false);
}

void SampleFlexAudioProcessorEditor::loadSample(juce::File& file)
{
	std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

	if ( reader.get() != nullptr)
	{
		auto duration = (float)reader->lengthInSamples / reader->sampleRate;

		if (duration < 1200)
		{
			processor.sampleBuffer.setSize((int)reader->numChannels, (int)reader->lengthInSamples);
			reader->read(&processor.sampleBuffer, 0, (int)reader->lengthInSamples, 0, true, true);
			//position = 0;
			this->sampleWavBox.thumbnail.setSource(new juce::FileInputSource(file));
			//processor.sampleFilePath = file.getFullPathName();
			processor.initVoices();

		}
		else
		{
			//TODO display error message
		}
	}
}

//==============================================================================
void SampleFlexAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setFont(15.0f);
}

void SampleFlexAudioProcessorEditor::resized()
{
	juce::Rectangle<int> rect(300, 0, 850, 850);
	int windowWidth = getLocalBounds().getWidth();
	int windowHeight = getLocalBounds().getHeight();

	sampleWavBox.setBounds(rect.removeFromTop(windowHeight / 3));

	int bottomThirdHeight = rect.getHeight();

	juce::Rectangle<int> bottomLeftSide(rect.removeFromLeft(windowWidth * 2 / 3));
	anchorControlPanel.setBounds(bottomLeftSide.removeFromTop(bottomThirdHeight / 2));

	spec.setBounds(0, 0, 300, 850);

	openSampleButton.setBounds(rect.removeFromTop(rect.getWidth() / 3));

	juce::Rectangle<int> adsrRect(getLocalBounds().removeFromBottom( getHeight() / 4 ));
	adsrRect.removeFromLeft(250);
	adsrRect.removeFromRight(25);
	juce::Rectangle<int> multAndGain = adsrRect.removeFromTop(75);
	adsrRect = adsrRect.removeFromTop(95);
	adsrStrip.setBounds(adsrRect);

	int multGainWidth = multAndGain.getWidth() / 4;
	multiplierSelector.setBounds(multAndGain.removeFromLeft(multGainWidth));
	gainSelector.setBounds(multAndGain.removeFromLeft(multGainWidth));
	rampSelector.setBounds(multAndGain.removeFromLeft(multGainWidth));
	thickenSelector.setBounds(multAndGain.removeFromLeft(multGainWidth));

	filterStrip.setBounds(rect.removeFromLeft(100));
	//lfoStrip.setBounds(rect.removeFromLeft(100));

	repaint();
}
