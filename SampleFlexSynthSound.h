/*
  ==============================================================================

    SampleFlexSynthSound.h
    Created: 8 Oct 2020 11:27:40am
    Author:  Administrator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SampleFlexSynthSound : public juce::SynthesiserSound
{
	//SampleFlexSynthSound() {}
	bool appliesToNote(int) override { return true; }
	bool appliesToChannel(int) override { return true; }
};
#pragma once
