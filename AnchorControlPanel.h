/*
  ==============================================================================

    AnchorControlPanel.h
    Created: 7 Oct 2020 11:45:58am
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnchorControlStrip.h"

//==============================================================================
/*
*/
class AnchorControlPanel : public Component
{
public:
	AnchorControlPanel(SampleFlexAudioProcessor& processor);
	~AnchorControlPanel();

	void paint(Graphics&) override;
	void resized() override;

	AnchorControlStrip anchor1;
	AnchorControlStrip anchor2;
	AnchorControlStrip anchor3;
	AnchorControlStrip anchor4;
	AnchorControlStrip anchor5;
	AnchorControlStrip anchor6;
	AnchorControlStrip anchor7;
	AnchorControlStrip anchor8;

private:

	SampleFlexAudioProcessor& processor;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnchorControlPanel)
};
