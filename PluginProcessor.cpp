/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SampleFlexSynthVoice.h"
#include "SampleFlexSynthSound.h"

//==============================================================================
SampleFlexAudioProcessor::SampleFlexAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    paramState(*this, nullptr, "PARAMETERS", createParamLayout())
#endif
{
}

SampleFlexAudioProcessor::~SampleFlexAudioProcessor()
{
}

//==============================================================================
const String SampleFlexAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SampleFlexAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SampleFlexAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SampleFlexAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SampleFlexAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SampleFlexAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SampleFlexAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SampleFlexAudioProcessor::setCurrentProgram (int index)
{
}

const String SampleFlexAudioProcessor::getProgramName (int index)
{
    return {};
}

void SampleFlexAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SampleFlexAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    //synth.setMinimumRenderingSubdivisionSize(); // MAYBE TODO
    synth.setNoteStealingEnabled(true);
    initVoices();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    spec.sampleRate = this->getSampleRate();
    filter.prepare(spec);
    filter.setEnabled(true);

    gain.prepare(spec);
    gain.setGainLinear(0);
}

void SampleFlexAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SampleFlexAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SampleFlexAudioProcessor::setParams()
{
    filter.setDrive(*paramState.getRawParameterValue("FILTERDRIVE"));
    filter.setCutoffFrequencyHz(*paramState.getRawParameterValue("FREQ"));
    filter.setResonance(*paramState.getRawParameterValue("Q"));
    filter.setMode((juce::dsp::LadderFilter<float>::Mode)(int) * paramState.getRawParameterValue("FILTERTYPE"));
    gain.setGainLinear(*paramState.getRawParameterValue("GAIN"));
}

void SampleFlexAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    buffer.clear();
    setParams();

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    juce::dsp::AudioBlock<float> ab(buffer);
    juce::dsp::ProcessContextReplacing<float> processContext(ab);
    //filter.process(processContext);
    gain.process(processContext);

    auto* channelData = buffer.getReadPointer(0, 0);

    for (auto i = 0; i < buffer.getNumSamples(); ++i)
        pushNextSampleIntoFifo(channelData[i]);

}

void SampleFlexAudioProcessor::pushNextSampleIntoFifo( float const & s)
{
    // if the fifo contains enough data, set a flag to say
// that the next line should now be rendered..
    if (fifoIndex == fftSize)       
    {
        if (!nextFFTBlockReady)    
        {
            std::fill(fftData.begin(), fftData.end(), 0.0f);
            std::copy(fifo.begin(), fifo.end(), fftData.begin());
            nextFFTBlockReady = true;
        }
        fifoIndex = 0;
    }
    fifo[(size_t)fifoIndex++] = s; 
}

//==============================================================================
bool SampleFlexAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SampleFlexAudioProcessor::createEditor()
{
    return new SampleFlexAudioProcessorEditor (*this);
}

//==============================================================================
void SampleFlexAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void SampleFlexAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SampleFlexAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SampleFlexAudioProcessor::createParamLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS1", "ANCHORPOS1", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS2", "ANCHORPOS2", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS3", "ANCHORPOS3", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS4", "ANCHORPOS4", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS5", "ANCHORPOS5", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS6", "ANCHORPOS6", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS7", "ANCHORPOS7", juce::NormalisableRange<float>(0, 1), 0));
    layout.add(std::make_unique<AudioParameterFloat>("ANCHORPOS8", "ANCHORPOS8", juce::NormalisableRange<float>(0, 1), 0));

    layout.add(std::make_unique<AudioParameterInt>("LCR1", "LCR1", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR2", "LCR2", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR3", "LCR3", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR4", "LCR4", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR5", "LCR5", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR6", "LCR6", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR7", "LCR7", 0, 2, 1));
    layout.add(std::make_unique<AudioParameterInt>("LCR8", "LCR8", 0, 2, 1));

    layout.add(std::make_unique<AudioParameterInt>("ONOFF1", "ONOFF1", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF2", "ONOFF2", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF3", "ONOFF3", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF4", "ONOFF4", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF5", "ONOFF5", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF6", "ONOFF6", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF7", "ONOFF7", 0, 1, 1));
    layout.add(std::make_unique<AudioParameterInt>("ONOFF8", "ONOFF8", 0, 1, 1));

    layout.add(std::make_unique<AudioParameterFloat>("FREQ", "FREQ", juce::NormalisableRange<float>(50, 10000), 50));
    layout.add(std::make_unique<AudioParameterFloat>("Q", "Q", juce::NormalisableRange<float>(0, 1), .5));
    layout.add(std::make_unique<AudioParameterInt>("FILTERTYPE", "FILTERTYPE", 0, 5, 1));
    layout.add(std::make_unique<AudioParameterFloat>("FILTERDRIVE", "FILTERDRIVE", juce::NormalisableRange<float>(1, 5), 1));

    layout.add(std::make_unique<AudioParameterFloat>("LFOFREQ", "LFOFREQ", juce::NormalisableRange<float>(0, 100), 2));
    layout.add(std::make_unique<AudioParameterInt>("LFOSHAPE", "LFOSHAPE", 0, 3, 2));
    layout.add(std::make_unique<AudioParameterInt>("LFOROUTING", "LFOROUTING", 0, 10, 0));

    layout.add(std::make_unique<AudioParameterInt>("LCR", "LCR", 0, 2, 1)); // can add lambdas here to map LCR strings to int
    layout.add(std::make_unique<AudioParameterInt>("MULTIPLIER", "MULTIPLIER", 0, 8, 1));
    layout.add(std::make_unique < AudioParameterFloat>("ATTACK", "ATTACK", juce::NormalisableRange<float>(0, 1), .5));
    layout.add(std::make_unique < AudioParameterFloat>("DECAY", "DECAY", juce::NormalisableRange<float>(0, 1), .5));
    layout.add(std::make_unique < AudioParameterFloat>("SUSTAIN", "SUSTAIN", juce::NormalisableRange<float>(0, 1), .5));
    layout.add(std::make_unique < AudioParameterFloat>("RELEASE", "RELEASE", juce::NormalisableRange<float>(0, 5), .5));
    layout.add(std::make_unique < AudioParameterFloat>("GAIN", "GAIN", juce::NormalisableRange<float>(0.001, .8), .05));
    layout.add(std::make_unique < AudioParameterFloat>("RAMP", "RAMP", juce::NormalisableRange<float>(0.0f, 0.5f), .01f));
    layout.add(std::make_unique < AudioParameterFloat>("THICKEN", "THICKEN", juce::NormalisableRange<float>(0.85f, 1.15f), 1.0f));

    return layout;
}

void SampleFlexAudioProcessor::initVoices()
{
    synth.clearVoices();

    for (auto i = 0; i < 11; i++)
    {
        synth.addVoice(new SampleFlexSynthVoice(*this));
    }
    synth.clearSounds();
    synth.addSound(new SampleFlexSynthSound());
}
