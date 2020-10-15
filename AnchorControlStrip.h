/*
  ==============================================================================

    AnchorControlStrip.h
    Created: 7 Oct 2020 11:46:13am
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class AnchorControlStrip : public Component
{
public:
	AnchorControlStrip(SampleFlexAudioProcessor& p, String anchorNum);
	~AnchorControlStrip();

	void paint(Graphics&) override;
	void resized() override;

	juce::Slider anchorPos;

private:
	String anchorNum;
	juce::Slider skew;
	juce::Slider lcr;
	juce::ToggleButton onOff;

	juce::Label anchorLabel;
	juce::Label skewLabel;
	juce::Label lcrLabel;
	juce::Label onOffLabel;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> anchorPosAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> skewAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lcrAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> onOffAttachment;

	SampleFlexAudioProcessor& processor;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnchorControlStrip)
};
