/*
  ==============================================================================

    FilterStrip.h
    Created: 7 Oct 2020 11:46:27am
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterStrip : public Component
{
public:
	FilterStrip(SampleFlexAudioProcessor& p);
	~FilterStrip();

	void paint(Graphics&) override;
	void resized() override;
	SampleFlexAudioProcessor& processor;

private:
	juce::Slider freq;
	juce::Slider q;
	juce::Slider type;
	juce::Slider drive;

	juce::Label freqLabel;
	juce::Label qLabel;
	juce::Label typeLabel;
	juce::Label driveLabel;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> qAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> typeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterStrip)
};
