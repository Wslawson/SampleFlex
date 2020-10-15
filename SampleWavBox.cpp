/*
  ==============================================================================

    SampleWavBox.cpp
    Created: 7 Oct 2020 11:46:57am
    Author:  Administrator

  ==============================================================================
*/

#include <JuceHeader.h>
#include <cstdio>
#include "SampleWavBox.h"
#include "AnchorControlPanel.h"
#include <cmath>


//==============================================================================
SampleWavBox::SampleWavBox(SampleFlexAudioProcessor& p, AnchorControlPanel& acp) : thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache), processor(p)
{
	setSize(200, 50);

	thumbnail.addChangeListener(this);
	formatManager.registerBasicFormats();
	
	colors.push_back(juce::Colours::darkblue);
	colors.push_back(juce::Colours::indianred);
	colors.push_back(juce::Colours::lightseagreen);
	colors.push_back(juce::Colours::lightyellow);
	colors.push_back(juce::Colours::orange );
	colors.push_back(juce::Colours::purple );
	colors.push_back(juce::Colours::lightpink);
	colors.push_back(juce::Colours::sandybrown);

	for (int i = 0; i < 8; i++)
	{
		processor.paramState.addParameterListener( anchorParameterIds.at(i), this);
		processor.paramState.addParameterListener(lcrParameterIds.at(i), this);
	}

}

SampleWavBox::~SampleWavBox()
{
}

void SampleWavBox::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::darkgoldenrod);
	g.drawRect(getLocalBounds(), 4);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(14.0f);

	juce::Rectangle<int> thumbnailBounds = getLocalBounds();
	if (thumbnail.getNumChannels() == 0)
		paintIfNoFileLoaded(g, thumbnailBounds);
	else
		paintIfFileLoaded(g, thumbnailBounds);

	juce::Colour color = juce::Colours::lightseagreen;
	
	for (int x = 0; x < anchorParameterIds.size(); x++)
	{
		g.setColour(colors.at(x));
		juce::Line<float> arrowTop1( anchorPos.at(x), 0, anchorPos.at(x), 7);
		juce::Line<float> arrowBottom1(anchorPos.at(x), getHeight(), anchorPos.at(x), getHeight() - 7);
		g.drawArrow(arrowTop1, 1, 10, 50);
		g.drawArrow(arrowBottom1, 1, 10, 50);
		g.fillRect(anchorPos.at(x), 0, 1, getHeight());

	}

	//// only draw left/right bounds if left/right are not the anchor
	//	
	//	lcrMode = (int)*processor.paramState.getRawParameterValue(lcrParameterIds.at(x));

	//	if (lcrMode == 0)
	//	{
	//		g.fillRect(rightBoundPos, 0, 1, getHeight());
	//		g.fillRect(leftBoundPos, 0, 1, getHeight());
	//	}
	//	else if (lcrMode == 1)
	//	{
	//		g.fillRect(rightBoundPos, 0, 1, getHeight());
	//	}
	//	else if (lcrMode == 2)
	//	{
	//		g.fillRect(leftBoundPos, 0, 1, getHeight());
	//	}
	//// highlight area between anchor and bounds
	//juce::Rectangle<int> boundsRect(leftBoundPos, 0, rightBoundPos - leftBoundPos, getHeight());
	//g.setColour(juce::Colours::lightgoldenrodyellow);
	//juce::FillType opaqueFill;
	//opaqueFill.setOpacity(0.3f);
	//g.setFillType(opaqueFill);
	//g.fillRect(boundsRect);
}

void SampleWavBox::paintIfNoFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds)
{
	g.setColour(juce::Colours::darkslategrey);
	g.fillRect(thumbnailBounds);
	g.setColour(juce::Colours::transparentWhite);
	g.drawFittedText("No File Loaded", thumbnailBounds, juce::Justification::centred, 1);
}

void SampleWavBox::paintIfFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds)
{
	g.setColour(juce::Colours::darkslategrey);
	g.fillRect(thumbnailBounds);
	g.setColour(juce::Colours::palevioletred);

	thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);
}
void SampleWavBox::resized()
{
}

void SampleWavBox::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if (source == &thumbnail) thumbnailChanged();
}

void SampleWavBox::thumbnailChanged()
{
	repaint();
}

void SampleWavBox::parameterChanged(const String& parameterID, float newValue)
{
	int width = this->getWidth();

	for (int x = 0; x < anchorParameterIds.size(); x++)
	{
		if (parameterID == anchorParameterIds.at(x))
		{
			anchorPos.at(x) = newValue * (float)width;
		}
	}

	for (int y = 0; y < lcrParameterIds.size(); y++)
	{
		if (parameterID == lcrParameterIds.at(y))
		{
			lcr.at(y) = (int)newValue;
		}
	}

	repaint();
}