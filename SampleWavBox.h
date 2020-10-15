/*
  ==============================================================================

    SampleWavBox.h
    Created: 7 Oct 2020 11:46:57am
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include <vector>
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AnchorControlPanel.h"


//==============================================================================
/*
*/
class SampleWavBox : public juce::Component, public juce::ChangeListener,  public juce::AudioProcessorValueTreeState::Listener
{
public:
	SampleWavBox(SampleFlexAudioProcessor& processor, AnchorControlPanel& acp);
	~SampleWavBox() override;

	void paint(juce::Graphics&) override;
	void resized() override;
	void paintIfFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds);
	void paintIfNoFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds);
	void SampleWavBox::parameterChanged(const String& parameterID, float newValue);
	juce::AudioThumbnailCache thumbnailCache;
	juce::AudioThumbnail thumbnail;
	juce::AudioFormatManager formatManager;

	std::vector< juce::String > anchorParameterIds = {
		(String)"ANCHORPOS1", (String)"ANCHORPOS2", (String)"ANCHORPOS3",
		(String)"ANCHORPOS4",(String)"ANCHORPOS5", (String)"ANCHORPOS6",
		(String)"ANCHORPOS7", (String)"ANCHORPOS8"
	};

	std::vector< juce::String > lcrParameterIds = {
	(String)"LCR1", (String)"LCR2", (String)"LCR3",
	(String)"LCR4",(String)"LCR5", (String)"LCR6",
	(String)"LCR7", (String)"LCR8"
	};

	std::vector< juce::Colour> colors;
	 

private:
	MessageManager::Lock mmLock;

	//FIELDS
	bool anchorPosChanged = false;
	int leftBoundPos = 0;
	int rightBoundPos = 0;
	int boundsOn = false;
	int lcrMode = 0;

	int anchorPos1, anchorPos2, anchorPos3, anchorPos4, anchorPos5, anchorPos6, anchorPos7, anchorPos8 = 0;
	std::vector<int> anchorPos = { 0,0,0,0,0,0,0,0 };
	std::vector<int> lcr  = { 0,0,0,0,0,0,0,0 };
	//std::vector<juce::Colour> colors = { new juce::Colour, new juce::Colour, new juce::Colour, new juce::Colour,
	//	new juce::Colour, new juce::Colour, new juce::Colour, new juce::Colour };

	//including to avoid errors  : listening by value tree
	int rightBound = 0;
	int leftBound = 0;

	//METHODS
	void changeListenerCallback(juce::ChangeBroadcaster* source);
	void thumbnailChanged();
	//void sliderValueChanged(juce::Slider* slider);
	void SampleWavBox::valueChanged(Value& value);

	SampleFlexAudioProcessor& processor;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleWavBox)
};
