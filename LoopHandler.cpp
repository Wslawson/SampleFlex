/*
  ==============================================================================

    LoopHandler.cpp
    Created: 8 Oct 2020 11:46:51am
    Author:  Administrator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LoopHandler.h"


LoopHandler::LoopHandler(SampleFlexAudioProcessor& p) : processor(p), avg(10)
{
	this->setBounds(440.0f);
}

// set bounds for each anchor using anchor pos and lcr type
void LoopHandler::setBounds(double const& freq)
{
	numSamples = (int)((processor.getSampleRate() / freq) * *processor.paramState.getRawParameterValue("MULTIPLIER"));
	ramp = ( (float)numSamples * 0.1f ) / (float)numSamples;

	for (int x = 0; x < 8; x++)
	{
		leftBound[x] = (int)(processor.sampleBuffer.getNumSamples() * *processor.paramState.getRawParameterValue("ANCHORPOS" + anchorNumbers.at(x)));
		lcr[x] = (int)*processor.paramState.getRawParameterValue("LCR" + anchorNumbers.at(x));
		onOff[x] = (int)*processor.paramState.getRawParameterValue("ONOFF" + anchorNumbers.at(x));

		numSamplesLeftInBound[x] = numSamples;
		totalSamplesInBound[x] = numSamples;

		switch (lcr[x])
		{
		case 0:
			break;
		case 1:
			leftBound[x] -= numSamples / 2; break;
		case 2:
			leftBound[x] -= numSamples; break;
		}
	}
	bufferIndex = leftBound[0];
	currentAnchorIndex = 0;
	rampCount = (int)(numSamples * *processor.paramState.getRawParameterValue("RAMP"));
	rampAmt = (float)( ( ( 1.0f/ (float)rampCount ) ) / 2.0f );
}

//move the buffer index forward, ensuring it remains in bounds
void LoopHandler::advanceBufferIndex()
{
	if (numSamplesLeftInBound[currentAnchorIndex] <= 0)
	{
		numSamplesLeftInBound[currentAnchorIndex] = totalSamplesInBound[currentAnchorIndex];

		do
		{
			currentAnchorIndex = (currentAnchorIndex + 1) % 8;
			onOff[currentAnchorIndex] = (int)*processor.paramState.getRawParameterValue("ONOFF" + anchorNumbers.at(currentAnchorIndex));
		} while (onOff[currentAnchorIndex] == 0 && currentAnchorIndex != 0);

		ramp = 0;
		bufferIndex = leftBound[currentAnchorIndex];
	}
	else
	{
		numSamplesLeftInBound[currentAnchorIndex] -= 1;
		bufferIndex++;

		if (numSamplesLeftInBound[currentAnchorIndex] >= totalSamplesInBound[currentAnchorIndex] - rampCount)
		{
			ramp += rampAmt;
		}
		else if (numSamplesLeftInBound[currentAnchorIndex] <= rampCount)
		{
			ramp -= rampAmt;
		}

		if (ramp > 1)
			ramp = 1;
		if (ramp < 0)
			ramp = 0;

		//ramp += (totalSamplesInBound[currentAnchorIndex] * 0.3f) / totalSamplesInBound[currentAnchorIndex];
		//ramp += 1 / (totalSamplesInBound[currentAnchorIndex] * 0.3f);
		//if (ramp > 1)
		//	ramp = 1;
	}
}

//returns the next sample in sequence
double LoopHandler::getNextSample()
{
	if ((bufferIndex < 0 || bufferIndex >= processor.sampleBuffer.getNumSamples()) && processor.sampleBuffer.getNumSamples() > 0)
	{
		bufferIndex = 0;
	}
	else if (processor.sampleBuffer.getNumSamples() <= 0)
	{
		return 0;
	}

	double sample = processor.sampleBuffer.getSample(0, bufferIndex);
	advanceBufferIndex();
	return sample * ramp; 
	//* ramp;
}

