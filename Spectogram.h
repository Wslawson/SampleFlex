/*
  ==============================================================================

    Spectogram.h
    Created: 9 Oct 2020 5:06:59pm
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Spectogram    : public Component, private juce::Timer
{
public:
    Spectogram( SampleFlexAudioProcessor& p);
    ~Spectogram();

    void paint (Graphics&) override;
    void resized() override;

    //static constexpr auto fftOrder = 10;               
    //static constexpr auto fftSize = 1 << fftOrder;    
    juce::dsp::FFT forwardFFT;                          
    juce::Image spectrogramImage;

    //std::array<float, fftSize> fifo;                   
    //std::array<float, fftSize * 2> fftData;             
    //int fifoIndex = 0;                                 
    //bool nextFFTBlockReady = false;                     

    void drawNextLineOfSpectogram();
    void timerCallback() override;

private:
    SampleFlexAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Spectogram)
};
