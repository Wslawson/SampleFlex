/*
  ==============================================================================

    ADSRStrip.h
    Created: 14 Oct 2020 7:43:06pm
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSRStrip    : public Component
{
public:
    ADSRStrip( SampleFlexAudioProcessor& p);
    ~ADSRStrip();

    void paint (Graphics&) override;
    void resized() override;

private:
    juce::Slider attackSelector;
    juce::Slider decaySelector;
    juce::Slider sustainSelector;
    juce::Slider releaseSelector;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    SampleFlexAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRStrip)
};
