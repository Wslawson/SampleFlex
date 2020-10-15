/*
  ==============================================================================

    AnchorControlPanel.cpp
    Created: 7 Oct 2020 11:45:58am
    Author:  Administrator

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnchorControlPanel.h"

//==============================================================================
AnchorControlPanel::AnchorControlPanel(SampleFlexAudioProcessor& p) : processor(p),
anchor1(p, "1"), anchor2(p, "2"), anchor3(p, "3"), anchor4(p, "4"),
anchor5(p, "5"), anchor6(p, "6"), anchor7(p, "7"), anchor8(p, "8")
{
	addAndMakeVisible(&anchor1);
	addAndMakeVisible(&anchor2);
	addAndMakeVisible(&anchor3);
	addAndMakeVisible(&anchor4);
	addAndMakeVisible(&anchor5);
	addAndMakeVisible(&anchor6);
	addAndMakeVisible(&anchor7);
	addAndMakeVisible(&anchor8);
}

AnchorControlPanel::~AnchorControlPanel()
{
}

void AnchorControlPanel::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(Colours::darkgoldenrod);
	g.drawRect(getLocalBounds(), 5);   // draw an outline around the component
	g.setColour(Colours::white);
	g.setFont(14.0f);
}

void AnchorControlPanel::resized()
{
	juce::Rectangle<int> bounds = getLocalBounds();
	anchor1.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor2.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor3.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor4.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor5.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor6.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor7.setBounds(bounds.removeFromLeft(getLocalBounds().getWidth() / 8));
	anchor8.setBounds(bounds);
	repaint();
}
