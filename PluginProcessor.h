/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class SampleFlexAudioProcessor  : public AudioProcessor
{
public:

    bool logOut = false;
    void initVoices();

    //resources
    juce::AudioSampleBuffer sampleBuffer;
    juce::AudioProcessorValueTreeState paramState;

    //Processing Chain
    juce::Synthesiser synth;
    juce::dsp::LadderFilter<float> filter;
    juce::dsp::Gain<float> gain;

    //==============================================================================
    SampleFlexAudioProcessor();
    ~SampleFlexAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static constexpr auto fftOrder = 10;                // [1]
    static constexpr auto fftSize = 1 << fftOrder;     // [2]
    //juce::dsp::FFT forwardFFT;                          // [3]
    //juce::Image spectrogramImage;

    std::array<float, fftSize> fifo;                    // [4]
    std::array<float, fftSize * 2> fftData;             // [5]
    int fifoIndex = 0;                                  // [6]
    bool nextFFTBlockReady = false;                     // [7]

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParamLayout();
    void setParams();
    void pushNextSampleIntoFifo( float const&  s);


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleFlexAudioProcessor)
};
