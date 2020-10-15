/*
  ==============================================================================

    LoopHandler.h
    Created: 8 Oct 2020 11:46:51am
    Author:  Administrator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

struct RunningAverage
{
public:
	RunningAverage(int bufferSize)
	{
		buffer = new float[bufferSize];
	}
	~RunningAverage()
	{
		delete[] buffer;
	}
	void addSample(float sample)
	{
		runningAverage = runningAverage * count;
		runningAverage = (runningAverage + sample) / ++count;
	}
	float getAverage()
	{
		return runningAverage;
	};
private:
	float* buffer = nullptr;
	int writeHead = 0;
	int count = 0;
	float runningAverage = 0;
};

class LoopHandler
{
private:
	int numSamples = 0;

	const juce::AudioSampleBuffer bufferCopy;

	int bufferIndex = 0;
	int currentAnchorIndex = 0;

	int leftBound[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int numSamplesLeftInBound[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int totalSamplesInBound[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int lcr[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int onOff[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<String> anchorNumbers = { "1", "2", "3", "4", "5", "6", "7", "8" };

	float ramp = 0;
	int rampCount = 0;
	float rampAmt = 0;

	void advanceBufferIndex();
	RunningAverage avg;

	enum mode
	{
		// skew determines absolute size for each anchor
		FREESELECT,

		// anchor size is computed such that repetition of all anchors will produce requested tone
		TONAL,

		// anchor size is computed such that each anchor, if looped, will produce requested tone.
		// in this mode, tone produced will be FREQ  / number anchors active;
		FREETONAL,
	};

public:
	SampleFlexAudioProcessor& processor;

	LoopHandler(SampleFlexAudioProcessor& p);
	void setBounds(double const& freq);
	double getNextSample();


};


#pragma once
