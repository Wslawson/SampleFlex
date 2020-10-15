/*
  ==============================================================================

    Spectogram.cpp
    Created: 9 Oct 2020 5:06:59pm
    Author:  Administrator

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spectogram.h"

//==============================================================================
Spectogram::Spectogram(SampleFlexAudioProcessor& p) : processor(p), forwardFFT(processor.fftOrder), 
spectrogramImage(juce::Image::RGB, 250, 250, true)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(getLocalBounds().getWidth(), getLocalBounds().getWidth() );
    setOpaque(true);
    startTimerHz(60);
}

Spectogram::~Spectogram()
{
}

void Spectogram::drawNextLineOfSpectogram()
{
    auto rightHandEdge = spectrogramImage.getWidth() - 1;
    auto imageHeight = spectrogramImage.getHeight();

    // first, shuffle our image leftwards by 1 pixel..
    spectrogramImage.moveImageSection(0, 0, 1, 0, rightHandEdge, imageHeight);         // [1]

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform(processor.fftData.data());                   // [2]

    // find the range of values produced, so we can scale our rendering to
    // show up the detail clearly
    auto maxLevel = juce::FloatVectorOperations::findMinAndMax(processor.fftData.data(), processor.fftSize / 2); // [3]

    for (auto y = 1; y < imageHeight; ++y)                                              // [4]
    {
        auto skewedProportionY = 1.0f - std::exp(std::log((float)y / (float)imageHeight) * 0.2f);
        auto fftDataIndex = (size_t)juce::jlimit(0, processor.fftSize / 2, (int)(skewedProportionY * processor.fftSize / 2));
        auto level = juce::jmap(processor.fftData[fftDataIndex], 0.0f, juce::jmax(maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);
        if (level < .1)
        {
            //level = 0;
        }
        spectrogramImage.setPixelAt(rightHandEdge, y, juce::Colour::fromHSV(level, 1.0f, level, 1.0f)); // [5]
    }
}

void Spectogram::timerCallback()
{
    if ( processor.nextFFTBlockReady )
    {
        drawNextLineOfSpectogram();
        processor.nextFFTBlockReady = false;
        repaint();
    }
}

void Spectogram::paint (Graphics& g)
{
    spectrogramImage.desaturate();
    g.drawImage(spectrogramImage, getLocalBounds().toFloat());
}

void Spectogram::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    spectrogramImage = spectrogramImage.rescaled( getLocalBounds().getWidth(), getLocalBounds().getHeight() );
}
