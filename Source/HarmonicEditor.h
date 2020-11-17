/*
  ==============================================================================

    HarmonicEditor.h
    Created: 10 Nov 2020 2:44:17pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "HarmonicSlider.h"

//==============================================================================
/*
*/
class HarmonicEditor  : public juce::Component
{
public:

    HarmonicEditor();
    ~HarmonicEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent&) override;
    void mouseExit(const juce::MouseEvent&) override;
    void mouseDown(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;

	struct Listener
	{
		virtual void onValueChange(double harmonics[50]) = 0;
	};

	void setListener(Listener* pTheListener);

private:
    
    bool isEntered;
    bool isDown;
    
    juce::OwnedArray<HarmonicSlider> harmonicSliders;

	double harmonicValues[50];
	int nHarmonics = 50;
	Listener* pListener = NULL;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonicEditor)
};
