/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SampleWavBox.h"
#include "AnchorControlStrip.h"
#include "AnchorControlPanel.h"
#include "FilterStrip.h"
#include "Spectogram.h"
#include "ADSRStrip.h"

//==============================================================================
/**
*/
class SampleFlexAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SampleFlexAudioProcessorEditor (SampleFlexAudioProcessor&);
    ~SampleFlexAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void loadSample( juce::File& file );
    void openSampleButtonClicked();


    juce::AudioFormatManager formatManager;

    juce::TextButton openSampleButton;
    SampleWavBox sampleWavBox;
    AnchorControlPanel anchorControlPanel;
    FilterStrip filterStrip;
    ADSRStrip adsrStrip;
    Spectogram spec;

    juce::Slider gainSelector;
    juce::Slider multiplierSelector;
    juce::Slider rampSelector;
    juce::Slider thickenSelector;

    juce::Label gainLabel;
    juce::Label multiplierLabel;
    juce::Label rampLabel;
    juce::Label thickenLabel;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> multiplierAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rampAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> thickenAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SampleFlexAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleFlexAudioProcessorEditor)
};
