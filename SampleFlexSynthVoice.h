/*
  ==============================================================================

    SampleFlexSynthVoice.h
    Created: 8 Oct 2020 11:27:29am
    Author:  Administrator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SampleFlexSynthSound.h"
#include "LoopHandler.h"

#pragma once
class SampleFlexSynthVoice : public juce::SynthesiserVoice
{
private:
	juce::ADSR env;
	juce::ADSR::Parameters envParams;
	LoopHandler loop;
	LoopHandler loop2;
	LoopHandler loop3;

	double frequencyOfA = 440.0;
	float envelope = 0;
	float sample = 0;
	double freq = 0;

public:
	SampleFlexAudioProcessor& processor;

	SampleFlexSynthVoice(SampleFlexAudioProcessor& p) : processor(p), loop(p), loop2(p), loop3(p)
	{
		env.setSampleRate(this->getSampleRate());
		env.setParameters(envParams);
		env.reset();
	}

	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast <SampleFlexSynthSound*>(sound) != nullptr;
	}

	void setPitchBend(int pitchWheelPos)
	{

	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
	{
		freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber, frequencyOfA);

		envParams.attack = *processor.paramState.getRawParameterValue("ATTACK");
		envParams.decay = *processor.paramState.getRawParameterValue("DECAY");
		envParams.sustain = *processor.paramState.getRawParameterValue("SUSTAIN");
		envParams.release = *processor.paramState.getRawParameterValue("RELEASE");

		env.setParameters(envParams);
		loop.setBounds(freq);
		loop2.setBounds(freq * *processor.paramState.getRawParameterValue("THICKEN") );
		//loop3.setBounds(freq * 1.25f);
		env.noteOn();
	}

	void stopNote(float velocity, bool allowTailOff) override
	{
		env.noteOff();
	}

	void pitchWheelMoved(int newPitchWheelValue) override
	{

	}

	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}

	void renderNextBlock(AudioBuffer <float>& outputBuffer, int startSample, int numSamples) override
	{
		for (int s = startSample; s < numSamples + startSample; s++)
		{
			envelope = env.getNextSample();
			sample = loop.getNextSample() + loop2.getNextSample(); // +loop3.getNextSample();

			for (int c = 0; c < outputBuffer.getNumChannels(); c++)
			{
				outputBuffer.addSample(c, s, sample * envelope);
			}

			if ( ! env.isActive() )
				this->clearCurrentNote();
		}
	}
};